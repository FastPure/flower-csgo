#pragma once
class __declspec( align( 16 ) ) vec_aligned : public vector
{
public:
    inline vec_aligned( void )
    {
    };
    inline vec_aligned( vec_t X , vec_t Y , vec_t Z )
    {
        init( X , Y , Z );
    }

public:
    explicit vec_aligned( const vector &vOther )
    {
        init( vOther.x , vOther.y , vOther.z );
    }

    vec_aligned& operator=( const vector &vOther )
    {
        init( vOther.x , vOther.y , vOther.z );
        return *this;
    }

    vec_aligned& operator=( const vec_aligned &vOther )
    {
        _mm_store_ps( base() , _mm_load_ps( vOther.base() ) );
        return *this;
    }

    float w;
};


#define   DISPSURF_FLAG_SURFACE           (1<<0)
#define   DISPSURF_FLAG_WALKABLE          (1<<1)
#define   DISPSURF_FLAG_BUILDABLE         (1<<2)
#define   DISPSURF_FLAG_SURFPROP1         (1<<3)
#define   DISPSURF_FLAG_SURFPROP2         (1<<4)

#define   CONTENTS_SOLID                0x1       
#define   CONTENTS_MOVEABLE             0x4000
#define   CONTENTS_MONSTER              0x2000000 
#define   CONTENTS_WINDOW               0x2
#define   CONTENTS_DEBRIS               0x4000000
#define   CONTENTS_HITBOX               0x40000000

#define   MASK_ALL                      (0xFFFFFFFF)
#define   MASK_SHOT                     (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

class handle_entity;
struct ray_;
class game_trace;
typedef game_trace trace_;
class collideable;
class trace_list;
class phys_collide;
struct cplane_;
struct virtualmeshlist_;

enum class trace_type
{
    everything = 0 ,
    world ,
    entities ,
    props ,
};

class trace_filter
{
public:
    virtual bool should_hit_entity( handle_entity *entity , int mask ) = 0;
    virtual trace_type get_trace_type() const = 0;
};

class trace_filter_ : public trace_filter
{
public:
    bool should_hit_entity( handle_entity* handle , int mask )
    {
        return !( handle == skip );
    }
    virtual trace_type get_trace_type() const
    {
        return trace_type::everything;
    }
    void* skip;
};

class entitys_only : public trace_filter
{
public:
    bool should_hit_entity( handle_entity* handle , int mask )
    {
        return !( handle == skip );
    }
    virtual trace_type get_trace_type() const
    {
        return trace_type::entities;
    }
    void* skip;
};

class world_only : public trace_filter
{
public:
    bool should_hit_entity( handle_entity* handle , int mask )
    {
        return false;
    }
    virtual trace_type get_trace_type() const
    {
        return trace_type::world;
    }
};

class props_only : public trace_filter
{
public:
    bool should_hit_entity( handle_entity* handle , int mask )
    {
        return false;
    }
    virtual trace_type get_trace_type() const
    {
        return trace_type::everything;
    }
};

class simple_filter : public trace_filter
{
public:
    simple_filter( PVOID pEnt )
    {
        current_ent = pEnt;
    }

    virtual bool should_hit_entity( handle_entity * handle , int mask )
    {
        return handle != current_ent;
    }

    virtual trace_type	get_trace_type() const
    {
        return trace_type::everything;
    }

    PVOID current_ent;
};

class hit_all : public trace_filter_
{
public:
    virtual bool should_hit_entity( handle_entity* handle , int mask )
    {
        return true;
    }
};

enum class trace_behavior
{
    kTRACE_COUNTER_SET = 0 ,
    kTRACE_COUNTER_INC ,
};

class ent_enum
{
public:
    virtual bool enum_ent( handle_entity * handle ) = 0;
};


struct brush_
{
    vector plane;               
    unsigned short bevel;    
    unsigned short thin;     
};

class phys_collide;

struct vcollide_
{
    unsigned short hit_solids : 15;
    unsigned short hit_packets : 1;
    unsigned short hit_size;
    phys_collide   **solids;
    char           *key_val;
    void           *user_data;
};

struct cmodel
{
    vector         mins , maxs;
    vector         origin;       
    int            head_node;
    vcollide_     collision_data;
};

struct csurface_t
{
    const char     *name;
    short          props;
    unsigned short flags;
};

struct ray_
{
    vec_aligned  start_; 
    vec_aligned  delta;  
    vec_aligned  start_offest;
    vec_aligned  extents;     
    const matrix_divided *transform;
    bool is_ray;  
    bool valid;     

    ray_() : transform( NULL )
    {
    }

    void init( vector const& start , vector const& end )
    {
        delta = end - start;

        valid = ( delta.lenght_sqr() != 0 );

        extents.init();

        transform = NULL;
        is_ray = true;

        start_offest.init();
        vector_extras::vector_copy( start , start_ );
    }

    void init( vector const& start , vector const& end , vector const& mins , vector const& maxs )
    {
        delta = end - start;

        transform = NULL;
        valid = ( delta.lenght_sqr() != 0 );

        extents = maxs - mins;
        extents *= 0.5f;
        is_ray = ( extents.lenght_sqr() < 1e-6 );

        start_offest = maxs + mins;
        start_offest *= 0.5f;
        start_ = start + start_offest;
        start_offest *= -1.0f;
    }
    vector invalid_delta() const
    {
        vector invalid;
        for ( int axis = 0; axis < 3; ++axis )
        {
            if ( delta[ axis ] != 0.0f )
            {
                invalid[ axis ] = 1.0f / delta[ axis ];
            }
            else
            {
                invalid[ axis ] = FLT_MAX;
            }
        }
        return invalid;
    }

private:
};

struct cplane_
{
    vector	normal;
    float	dist;
    byte	type;			
    byte	bits;		
    byte	pad[ 2 ];

};

class base_trace
{
public:
    bool hit_surface( void )
    {
        return ( ( flags & DISPSURF_FLAG_SURFACE ) != 0 );
    }
    bool hit_walkable( void )
    {
        return ( ( flags & DISPSURF_FLAG_WALKABLE ) != 0 );
    }
    bool hit_buildable( void )
    {
        return ( ( flags & DISPSURF_FLAG_BUILDABLE ) != 0 );
    }
    bool hit_surface1( void )
    {
        return ( ( flags & DISPSURF_FLAG_SURFPROP1 ) != 0 );
    }
    bool hit_surface2( void )
    {
        return ( ( flags & DISPSURF_FLAG_SURFPROP2 ) != 0 );
    }

public:

    vector         start_pos;                
    vector         end_pos;                       
    cplane_        plane;

    float          fraction;               

    int            contents;               
    unsigned short flags;                    

    bool           all_solid;                
    bool           start_solid;                   

    base_trace()
    {
    }

};

class game_trace : public base_trace
{
public:
    bool                    hit_world() const;
    bool                    dint_hit_world() const;
    int                     get_index() const;
    bool                    hit() const;
    bool					is_visible() const;

public:

    float                   solid;
    csurface_t              surface;
    int                     hit_group;
    short                   physics_bone;
    unsigned short          world_index;
    csplayer*               ent;
    int                     hitbox;

    game_trace()
    {
    }

private:
    game_trace( const game_trace& vOther );
};

class trace
{
public:
    int get_point( const vector &abs_pos , int mask = MASK_ALL , handle_entity** entity = NULL )
    {
        using original = int( __thiscall* )( void* , const vector& , int , handle_entity** );
        return globals::tools::get_virtualfn<0 , original>( this )( this , abs_pos , mask , entity );
    }

    void ray_to_entity( const ray_ &ray , unsigned int mask , handle_entity * entity , game_trace * trace )
    {
        using original = void( __thiscall* )( void* , const ray_& , unsigned int , handle_entity* , game_trace * );
        return globals::tools::get_virtualfn<3 , original>( this )( this , ray , mask , entity , trace );
    }

    void trace_ray( const ray_ &ray , unsigned int mask , trace_filter * filter , game_trace * trace )
    {
        using original = void( __thiscall* )( void* , const ray_& , unsigned int , trace_filter* , game_trace * );
        return globals::tools::get_virtualfn<5 , original>( this )( this , ray , mask , filter , trace );
    }
};
