#pragma once
class csplayer
{
public:
    uint32_t get_armor()
    {
        return *reinterpret_cast< uint32_t * >( this + globals::game_resources::armor );
    }

    uint32_t get_health()
    {
        return *reinterpret_cast< uint32_t * >( this + globals::game_resources::health );
    }

    uint32_t get_team()
    {
        return *reinterpret_cast< uint32_t * >( this + globals::game_resources::team );
    }

    uint32_t get_flags()
    {
        return *reinterpret_cast< uint32_t * >( this + globals::game_resources::flags );
    }

    uint32_t get_shots_fired()
    {
        return *reinterpret_cast< uint32_t * >( this + globals::game_resources::shots_fired );
    }

    float * get_flash_duration()
    {
        return reinterpret_cast< float * >( this + globals::game_resources::flash_duration );
    }

    bool get_dormant()
    {
        return *reinterpret_cast< bool * >( this + globals::game_resources::dormant );
    }

    bool is_respawning()
    {
        return *reinterpret_cast< bool * >( this + globals::game_resources::respawning );
    }

    bool is_scoped()
    {
        return *reinterpret_cast< bool * >( this + globals::game_resources::scoped );
    }

    float get_next_fire_time()
    {
        return *reinterpret_cast< float * >( this + globals::game_resources::next_fire );
    }

    float get_lower_body_yaw()
    {
        return *reinterpret_cast< float * >( this + globals::game_resources::lower_body_yaw );
    }

    bool is_pin_puled()
    {
        return *reinterpret_cast< bool * >( this + globals::game_resources::pin_pulled );
    }

    float get_throw_time()
    {
        return *reinterpret_cast< float * >( this + globals::game_resources::trow_time );
    }
    
    uint32_t get_tick_base()
    {
        return *reinterpret_cast< uint32_t * >( this + globals::game_resources::tick_base );
    }

    uint32_t get_move_type()
    {
        return *reinterpret_cast< uint32_t * >( this + globals::game_resources::move_type );
    }

    uint32_t get_active_wep_index()
    {
        return *reinterpret_cast< int* >( uintptr_t( this ) + globals::game_resources::active_weapon ) & 0xFFF;
    }

    uint32_t get_item_def_index()
    {
        return *reinterpret_cast< uint32_t * >( this + globals::game_resources::item_def_index );
    }

    uint32_t get_current_ammo_m1()
    {
        return *reinterpret_cast< uint32_t * >( this + globals::game_resources::current_ammo_m1 );
    }

    uint32_t get_current_ammo_m2()
    {
        return *reinterpret_cast< uint32_t * >( this + globals::game_resources::current_ammo_m1 );
    }

    uint32_t get_owner_entity()
    {
        return *reinterpret_cast< uint32_t * >( this + globals::game_resources::owner_entity );
    }

    vector get_aim_punch()
    {
        return *reinterpret_cast< vector * >( this + globals::game_resources::aim_punch );
    }

    vector get_origin()
    {
        return *reinterpret_cast< vector* >( this + globals::game_resources::origin );
    }

    vector get_view_offset()
    {
        return *reinterpret_cast< vector* >( this + globals::game_resources::view_offset );
    }
    
    vector get_velocity()
    {
        return *reinterpret_cast< vector* >( this + globals::game_resources::velocity );
    }

    vector get_eye_pos()
    {
        return this->get_origin() + this->get_view_offset();
    }

    vector get_eye_angle()
    {
        return *reinterpret_cast< vector* >( this + globals::game_resources::eye_angle );
    }


    vector * set_eye_angles()
    {
        return reinterpret_cast< vector* >( this + globals::game_resources::eye_angle );
    }


    float get_simulation_time()
    {
        return *reinterpret_cast< float * >( this + globals::game_resources::simulation_time );
    }

    void render_bounds( vector& mins , vector& maxs )
    {
        void* original = ( void* ) ( this + 0x4 );
        typedef void( __thiscall* fn )( void* , vector& , vector& );
        return globals::tools::get_virtualfn<17 , fn>( original )( original , mins , maxs );
    }

    vector& get_abs_origin()
    {
        using original = vector & ( __thiscall* )( void* );
        return globals::tools::get_virtualfn<10 , original>( this )( this );
    }

    bool setup_bones( matrix_divided * bone_matrix , uint32_t max_bones , uint32_t bone_max , float time = 0 )
    {
        void* renderable = ( void* ) ( this + 0x4 );
        typedef bool( __thiscall* Fn )( void* , matrix_divided * , uint32_t , uint32_t , float );
        return globals::tools::get_virtualfn<13 , Fn>( renderable )( renderable , bone_matrix , max_bones , bone_max , time );
    }
    
    model_ * get_model()
    {
        void* renderable = ( void* ) ( this + 0x4 );
        typedef model_*( __thiscall* fn )( void* );
        return globals::tools::get_virtualfn<8 , fn>( renderable )( renderable );
    }

    int draw_model( uint32_t flags , const int &instance )
    {
        void* renderable = ( void* ) ( this + 0x4 );
        typedef int( __thiscall* Fn )( void* , uint32_t , const int & );
        return globals::tools::get_virtualfn<9 , Fn>( renderable )( renderable , flags , instance );
    }

    model_instance get_model_instance()
    {
        void* renderable = ( void* ) ( this + 0x4 );
        typedef model_instance( __thiscall* Fn )( void* );
        return globals::tools::get_virtualfn<30 , Fn>( renderable )( renderable );
    }

    vector get_bone_pos( int i )
    {
        matrix_divided boneMatrix[ 128 ];
        if ( this->setup_bones( boneMatrix , 128 , 0x00000100 , GetTickCount64() ) )
        {
            return vector( boneMatrix[ i ][ 0 ][ 3 ] , boneMatrix[ i ][ 1 ][ 3 ] , boneMatrix[ i ][ 2 ][ 3 ] );
        }
        return vector( 0 , 0 , 0 );
    }

    client_class* get_client_class()
    {
        void* networkable = ( void* ) ( this + 0x8 );
        typedef client_class*( __thiscall* fn )( void* );
        return globals::tools::get_virtualfn<2 , fn>( networkable )( networkable );
    }

    anim_state * get_anim_state ()
    {
        return *reinterpret_cast< anim_state** >( uintptr_t( this ) + globals::game_resources::anim_state );
    }

    void set_angle( vector angle )
    {
        typedef void( __thiscall* set_angle_fn )( void* , const vector & );
        static set_angle_fn set_angle_ = ( set_angle_fn ) 
            ( ( uintptr_t ) globals::tools::signature( "client_panorama.dll" , "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1" ) );
        set_angle_( this , angle );
    }

    const weapon_struct *get_weapon_info()
    {
        return flower_sdk::p_wep_system->get_wep_data( this->get_item_def_index() );
    }

    bool has_scope()
    {
        int wep_index = this->get_item_def_index();
        return wep_index == WEAPON_G3SG1
            || wep_index == WEAPON_SCAR20
            || wep_index == WEAPON_AWP
            || wep_index == WEAPON_AUG
            || wep_index == WEAPON_SG558
            || wep_index == WEAPON_SSG08;
    }


    bool is_grenade()
    {
        return this->get_item_def_index() >= 43 && this->get_item_def_index() <= 48;
    }

    bool is_being_throw()
    {
        if ( !this->is_pin_puled() )
        {
            float throwtime = this->get_throw_time();
            if ( ( throwtime > 0 ) && ( throwtime < flower_sdk::p_globals_var_base->curtime ) )
                return true;
        }
        return false;
    }
    
};