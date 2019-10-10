#pragma once

struct mstudiobbox_t
{
    int     bone;
    int     group;
    vector  bbmin;
    vector  bbmax;
    int     hitbox_name_index;
    int32_t     pad_1[ 3 ];
    float       radius;
    int32_t     pad_2[ 4 ];

    char* get_hitbox_name( void )
    {
        return ( ( char* ) this ) + hitbox_name_index;
    }
};
struct mstudiohitboxset_t
{
    int    name_index;
    inline char* const     get_name( void ) const
    {
        return ( ( char* ) this ) + name_index;
    }
    int      num_hitboxes;
    int      hitbox_index;

    inline mstudiobbox_t*   get_hitbox( int i ) const
    {
        return ( mstudiobbox_t* ) ( ( ( BYTE* ) this ) + hitbox_index ) + i;
    };
};

struct mstudiobone_t
{
    int					name_index;
    inline char * const name( void ) const
    {
        return ( ( char * ) this ) + name_index;
    }
    int		 			parent;		
    int					bonecontroller[ 6 ];	

                                           
    vector				pos;
    float                           quat[ 4 ];
    vector			rot;
    vector				posscale;
    vector				rotscale;

    matrix_divided			pose_to_bone;
    float                           alignment[ 4 ];
    int					flags;
    int					proctype;
    int					procindex;		
    mutable int			physics_bone;	
    inline void *pProcedure() const
    {
        if ( procindex == 0 ) return NULL; else return  ( void * ) ( ( ( byte * ) this ) + procindex );
    };
    int					surface_prop_idx;	
    inline char * const surface_prop( void ) const
    {
        return ( ( char * ) this ) + surface_prop_idx;
    }
    int					contents;		

    int					unused[ 8 ];		

    mstudiobone_t()
    {
    }
private:
    mstudiobone_t( const mstudiobone_t& vOther );
};


struct studiohdr_t
{
    int                                     id;
    int                                     version;

    int                                     checksum;

    char                            name[ 64 ];
    int                                     length;


    vector                          eyeposition;

    vector                          illumposition;

    vector                          hull_min;
    vector                          hull_max;

    vector                          view_bbmin;
    vector                          view_bbmax;

    int                                     flags;

    int                                     numbones;
    int                                     boneindex;

    inline mstudiobone_t *get_bone( int i ) const
    {
        return ( mstudiobone_t * ) ( ( ( BYTE * ) this ) + boneindex ) + i;
    };

    int                                     numbonecontrollers;
    int                                     bonecontrollerindex;

    int                                     numhitboxsets;
    int                                     hitboxsetindex;

    mstudiohitboxset_t* GetHitboxSet( int i ) const
    {
        return ( mstudiohitboxset_t* ) ( ( ( BYTE* ) this ) + hitboxsetindex ) + i;
    }

    inline mstudiobbox_t* get_hitbox( int i , int set ) const
    {
        mstudiohitboxset_t const* s = GetHitboxSet( set );

        if ( !s )
            return NULL;

        return s->get_hitbox( i );
    }

    inline int GetHitboxCount( int set ) const
    {
        mstudiohitboxset_t const* s = GetHitboxSet( set );

        if ( !s )
            return 0;

        return s->num_hitboxes;
    }

    int                                     numlocalanim;
    int                                     localanimindex;

    int                                     numlocalseq;
    int                                     localseqindex;

    mutable int                     activitylistversion;
    mutable int                     eventsindexed;

    int                                     numtextures;
    int                                     textureindex;

    int                                     numcdtextures;
    int                                     cdtextureindex;

    int                                     numskinref;
    int                                     numskinfamilies;
    int                                     skinindex;

    int                                     numbodyparts;
    int                                     bodypartindex;

    int                                     numlocalattachments;
    int                                     localattachmentindex;

    int                                     numlocalnodes;
    int                                     localnodeindex;
    int                                     localnodenameindex;

    int                                     numflexdesc;
    int                                     flexdescindex;

    int                                     numflexcontrollers;
    int                                     flexcontrollerindex;

    int                                     numflexrules;
    int                                     flexruleindex;

    int                                     numikchains;
    int                                     ikchainindex;

    int                                     nummouths;
    int                                     mouthindex;

    int                                     numlocalposeparameters;
    int                                     localposeparamindex;

    int                                     surfacepropindex;

    int                                     keyvalueindex;
    int                                     keyvaluesize;


    int                                     numlocalikautoplaylocks;
    int                                     localikautoplaylockindex;

    float                           mass;
    int                                     contents;

    int                                     numincludemodels;
    int                                     includemodelindex;

    mutable void            *virtualModel;

    int                                     szanimblocknameindex;
    int                                     numanimblocks;
    int                                     animblockindex;

    mutable void            *animblockModel;

    int                                     bonetablebynameindex;

    void                            *pVertexBase;
    void                            *pIndexBase;

    BYTE                            constdirectionallightdot;

    BYTE                            rootLOD;

    BYTE                            numAllowedRootLODs;

    BYTE                            unused[ 1 ];

    int                                     unused4;

    int                                     numflexcontrollerui;
    int                                     flexcontrolleruiindex;
    float                           flVertAnimFixedPointScale;
    int                                     unused3[ 1 ];
    int                                     studiohdr2index;
    int                                     unused2[ 1 ];
};

class model_;
class model
{
public:
    inline void* get_model( int index )
    {
        using original = void*( __thiscall* )( void* , int );
        return globals::tools::get_virtualfn<1 , original>( this )( this , index );
    }

    int	get_model_index( const char * name )
    {
        using original = int( __thiscall* )( void* , const char* );
        return globals::tools::get_virtualfn<2 , original>( this )( this , name );
    }

    const char *get_model_name( const model_ *mod )
    {
        using original = const char *( __thiscall* )( void* , const model_ * );
        return globals::tools::get_virtualfn<3 , original>( this )( this , mod );
    }


    studiohdr_t *get_studio_model( const model_ *mod )
    {
        using original = studiohdr_t * ( __thiscall* )( void* , const model_ * );
        return globals::tools::get_virtualfn<32 , original>( this )( this , mod );
    }
};

#pragma once

enum PreviewImageRetVal_t
{
    MATERIAL_PREVIEW_IMAGE_BAD = 0 ,
    MATERIAL_PREVIEW_IMAGE_OK ,
    MATERIAL_NO_PREVIEW_IMAGE ,
};

enum MaterialVarFlags_t
{
    MATERIAL_VAR_DEBUG = ( 1 << 0 ) ,
    MATERIAL_VAR_NO_DEBUG_OVERRIDE = ( 1 << 1 ) ,
    MATERIAL_VAR_NO_DRAW = ( 1 << 2 ) ,
    MATERIAL_VAR_USE_IN_FILLRATE_MODE = ( 1 << 3 ) ,
    MATERIAL_VAR_VERTEXCOLOR = ( 1 << 4 ) ,
    MATERIAL_VAR_VERTEXALPHA = ( 1 << 5 ) ,
    MATERIAL_VAR_SELFILLUM = ( 1 << 6 ) ,
    MATERIAL_VAR_ADDITIVE = ( 1 << 7 ) ,
    MATERIAL_VAR_ALPHATEST = ( 1 << 8 ) ,
    //MATERIAL_VAR_UNUSED = (1 << 9),
    MATERIAL_VAR_ZNEARER = ( 1 << 10 ) ,
    MATERIAL_VAR_MODEL = ( 1 << 11 ) ,
    MATERIAL_VAR_FLAT = ( 1 << 12 ) ,
    MATERIAL_VAR_NOCULL = ( 1 << 13 ) ,
    MATERIAL_VAR_NOFOG = ( 1 << 14 ) ,
    MATERIAL_VAR_IGNOREZ = ( 1 << 15 ) ,
    MATERIAL_VAR_DECAL = ( 1 << 16 ) ,
    MATERIAL_VAR_ENVMAPSPHERE = ( 1 << 17 ) , // OBSOLETE
    MATERIAL_VAR_UNUSED = ( 1 << 18 ) , // UNUSED
    MATERIAL_VAR_ENVMAPCAMERASPACE = ( 1 << 19 ) , // OBSOLETE
    MATERIAL_VAR_BASEALPHAENVMAPMASK = ( 1 << 20 ) ,
    MATERIAL_VAR_TRANSLUCENT = ( 1 << 21 ) ,
    MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = ( 1 << 22 ) ,
    MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = ( 1 << 23 ) , // OBSOLETE
    MATERIAL_VAR_OPAQUETEXTURE = ( 1 << 24 ) ,
    MATERIAL_VAR_ENVMAPMODE = ( 1 << 25 ) , // OBSOLETE
    MATERIAL_VAR_SUPPRESS_DECALS = ( 1 << 26 ) ,
    MATERIAL_VAR_HALFLAMBERT = ( 1 << 27 ) ,
    MATERIAL_VAR_WIREFRAME = ( 1 << 28 ) ,
    MATERIAL_VAR_ALLOWALPHATOCOVERAGE = ( 1 << 29 ) ,
    MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = ( 1 << 30 ) ,
    MATERIAL_VAR_VERTEXFOG = ( 1 << 31 ) ,
};

typedef unsigned short model_instance;
typedef void* LightCacheHandle_t;
typedef void* StudioDecalHandle_t;
typedef int OverrideType_t;
typedef int ImageFormat;
typedef int VertexFormat_t;
typedef int MaterialPropertyTypes_t;

class IClientRenderable;
class material;
class CStudioHdr;
class IMatRenderContext;
class DataCacheHandle_t;
class ITexture;
class IMaterialVar;
class KeyValues;
struct model_t;
struct mstudioanimdesc_t;
struct mstudioseqdesc_t;
struct Ray_t;
struct DrawModelInfo_t;
struct studiohwdata_t;
struct MaterialLightingState_t;
struct ColorMeshInfo_t;

struct DrawModelState_t
{
    studiohdr_t*            m_pStudioHdr;
    studiohwdata_t*         m_pStudioHWData;
    IClientRenderable*      m_pRenderable;
    const matrix_divided*      m_pModelToWorld;
    StudioDecalHandle_t     m_decals;
    int                     m_drawFlags;
    int                     m_lod;
};

struct StaticPropRenderInfo_t
{
    const matrix_divided*      pModelToWorld;
    const model_t*          pModel;
    IClientRenderable*      pRenderable;
    vector*                 pLightingOrigin;
    short                   skin;
    model_instance   instance;
};

struct model_render_info
{
    vector                  origin;
    vector                  angles;
    char					pad[ 0x4 ];
    IClientRenderable*      pRenderable;
    const model_t*          model;
    const matrix_divided*      pModelToWorld;
    const matrix_divided*      pLightingOffset;
    const vector*           pLightingOrigin;
    int                     flags;
    int                     entity_index;
    int                     skin;
    int                     body;
    int                     hitboxset;
    model_instance   instance;

    model_render_info()
    {
        pModelToWorld = NULL;
        pLightingOffset = NULL;
        pLightingOrigin = NULL;
    }
};

struct LightingQuery_t
{
    vector                  m_LightingOrigin;
    model_instance   m_InstanceHandle;
    bool                    m_bAmbientBoost;
};

struct StaticLightingQuery_t : public LightingQuery_t
{
    IClientRenderable*        m_pRenderable;
};

class material
{
public:
    virtual const char*             GetName() const = 0;
    virtual const char*             GetTextureGroupName() const = 0;
    virtual PreviewImageRetVal_t    GetPreviewImageProperties( int *width , int *height , ImageFormat *imageFormat , bool* isTranslucent ) const = 0;
    virtual PreviewImageRetVal_t    GetPreviewImage( unsigned char *data , int width , int height , ImageFormat imageFormat ) const = 0;
    virtual int                     GetMappingWidth() = 0;
    virtual int                     GetMappingHeight() = 0;
    virtual int                     GetNumAnimationFrames() = 0;
    virtual bool                    InMaterialPage( void ) = 0;
    virtual    void                 GetMaterialOffset( float *pOffset ) = 0;
    virtual void                    GetMaterialScale( float *pScale ) = 0;
    virtual material*              GetMaterialPage( void ) = 0;
    virtual IMaterialVar*           find_var( const char *varName , bool *found , bool complain = true ) = 0;
    virtual void                    IncrementReferenceCount( void ) = 0;
    virtual void                    DecrementReferenceCount( void ) = 0;
    inline void                     AddRef()
    {
        IncrementReferenceCount();
    }
    inline void                     Release()
    {
        DecrementReferenceCount();
    }
    virtual int                     GetEnumerationID( void ) const = 0;
    virtual void                    GetLowResColorSample( float s , float t , float *color ) const = 0;
    virtual void                    RecomputeStateSnapshots() = 0;
    virtual bool                    IsTranslucent() = 0;
    virtual bool                    IsAlphaTested() = 0;
    virtual bool                    IsVertexLit() = 0;
    virtual VertexFormat_t          GetVertexFormat() const = 0;
    virtual bool                    HasProxy( void ) const = 0;
    virtual bool                    UsesEnvCubemap( void ) = 0;
    virtual bool                    NeedsTangentSpace( void ) = 0;
    virtual bool                    NeedsPowerOfTwoFrameBufferTexture( bool bCheckSpecificToThisFrame = true ) = 0;
    virtual bool                    NeedsFullFrameBufferTexture( bool bCheckSpecificToThisFrame = true ) = 0;
    virtual bool                    NeedsSoftwareSkinning( void ) = 0;
    virtual void                    alpha_modulate( float alpha ) = 0;
    virtual void                    color_modulate( float r , float g , float b ) = 0;
    virtual void                    set_material_flag( MaterialVarFlags_t flag , bool on ) = 0;
    virtual bool                    GetMaterialVarFlag( MaterialVarFlags_t flag ) const = 0;
    virtual void                    GetReflectivity( vector& reflect ) = 0;
    virtual bool                    GetPropertyFlag( MaterialPropertyTypes_t type ) = 0;
    virtual bool                    IsTwoSided() = 0;
    virtual void                    SetShader( const char *pShaderName ) = 0;
    virtual int                     GetNumPasses( void ) = 0;
    virtual int                     GetTextureMemoryBytes( void ) = 0;
    virtual void                    Refresh() = 0;
    virtual bool                    NeedsLightmapBlendAlpha( void ) = 0;
    virtual bool                    NeedsSoftwareLighting( void ) = 0;
    virtual int                     ShaderParamCount() const = 0;
    virtual IMaterialVar**          GetShaderParams( void ) = 0;
    virtual bool                    IsErrorMaterial() const = 0;
    virtual void                    Unused() = 0;
    virtual float                   GetAlphaModulation() = 0;
    virtual void                    GetColorModulation( float *r , float *g , float *b ) = 0;
    virtual bool                    IsTranslucentUnderModulation( float fAlphaModulation = 1.0f ) const = 0;
    virtual IMaterialVar*           FindVarFast( char const *pVarName , unsigned int *pToken ) = 0;
    virtual void                    SetShaderAndParams( KeyValues *pKeyValues ) = 0;
    virtual const char*             GetShaderName() const = 0;
    virtual void                    DeleteIfUnreferenced() = 0;
    virtual bool                    IsSpriteCard() = 0;
    virtual void                    CallBindProxy( void *proxyData ) = 0;
    virtual void                    RefreshPreservingMaterialVars() = 0;
    virtual bool                    WasReloadedFromWhitelist() = 0;
    virtual bool                    SetTempExcluded( bool bSet , int nExcludedDimensionLimit ) = 0;
    virtual int                     GetReferenceCount() const = 0;
};

class render_view
{
public:

    virtual void DrawBrushModel( void* baseentity , model_t* model , const vector& origin , const vector& angles , bool sort ) = 0;

    virtual void DrawIdentityBrushModel( void * pList , model_t* model ) = 0;

    virtual void TouchLight( struct dlight_t* light ) = 0;

    virtual void Draw3DDebugOverlays( void ) = 0;

    virtual void set_blend( float blend ) = 0;
};


class model_render
{
public:
    virtual int                     DrawModel( int flags , IClientRenderable *pRenderable , model_instance instance , int entity_index , const model_t *model , vector const& origin , vector const& angles , int skin , int body , int hitboxset , const matrix_divided *modelToWorld = NULL , const matrix_divided *pLightingOffset = NULL ) = 0;
    virtual void                    force_material_override( material *newMaterial , OverrideType_t nOverrideType = 0 , int nOverrides = 0 ) = 0;
    virtual bool                    IsForcedMaterialOverride( void ) = 0;
    virtual void                    SetViewTarget( const CStudioHdr *pStudioHdr , int nBodyIndex , const vector& target ) = 0;
    virtual model_instance   CreateInstance( IClientRenderable *pRenderable , LightCacheHandle_t *pCache = NULL ) = 0;
    virtual void                    DestroyInstance( model_instance handle ) = 0;
    virtual void                    SetStaticLighting( model_instance handle , LightCacheHandle_t* pHandle ) = 0;
    virtual LightCacheHandle_t      GetStaticLighting( model_instance handle ) = 0;
    virtual bool                    ChangeInstance( model_instance handle , IClientRenderable *pRenderable ) = 0;
    virtual void                    AddDecal( model_instance handle , Ray_t const& ray , vector const& decalUp , int decalIndex , int body , bool noPokeThru , int maxLODToDecal ) = 0;
    virtual void                    RemoveAllDecals( model_instance handle ) = 0;
    virtual bool                    ModelHasDecals( model_instance handle ) = 0;
    virtual void                    RemoveAllDecalsFromAllModels() = 0;
    virtual matrix_divided *            DrawModelShadowSetup( IClientRenderable *pRenderable , int body , int skin , DrawModelInfo_t *pInfo , matrix_divided *pCustomBoneToWorld = NULL ) = 0;
    virtual void                    DrawModelShadow( IClientRenderable *pRenderable , const DrawModelInfo_t &info , matrix_divided *pCustomBoneToWorld = NULL ) = 0;
    virtual bool                    RecomputeStaticLighting( model_instance handle ) = 0;
    virtual void                    ReleaseAllStaticPropColorData( void ) = 0;
    virtual void                    RestoreAllStaticPropColorData( void ) = 0;
    virtual int                     DrawModelEx( model_render_info &pInfo ) = 0;
    virtual int                     DrawModelExStaticProp( model_render_info &pInfo ) = 0;
    virtual bool                    DrawModelSetup( model_render_info &pInfo , DrawModelState_t *pState , matrix_divided **ppBoneToWorldOut ) = 0;
    virtual void                    DrawModelExecute( IMatRenderContext* ctx , const DrawModelState_t& state , const model_render_info& pInfo , matrix_divided* pCustomBoneToWorld = NULL ) = 0;
    virtual void                    SetupLighting( const vector &vecCenter ) = 0;
    virtual int                     DrawStaticPropArrayFast( StaticPropRenderInfo_t *pProps , int count , bool bShadowDepth ) = 0;
    virtual void                    SuppressEngineLighting( bool bSuppress ) = 0;
    virtual void                    SetupColorMeshes( int nTotalVerts ) = 0;
    virtual void                    SetupLightingEx( const vector &vecCenter , model_instance handle ) = 0;
    virtual bool                    GetBrightestShadowingLightSource( const vector &vecCenter , vector& lightPos , vector& lightBrightness , bool bAllowNonTaggedLights ) = 0;
    virtual void                    ComputeLightingState( int nCount , const LightingQuery_t *pQuery , MaterialLightingState_t *pState , ITexture **ppEnvCubemapTexture ) = 0;
    virtual void                    GetModelDecalHandles( StudioDecalHandle_t *pDecals , int nDecalStride , int nCount , const model_instance *pHandles ) = 0;
    virtual void                    ComputeStaticLightingState( int nCount , const StaticLightingQuery_t *pQuery , MaterialLightingState_t *pState , MaterialLightingState_t *pDecalState , ColorMeshInfo_t **ppStaticLighting , ITexture **ppEnvCubemapTexture , DataCacheHandle_t *pColorMeshHandles ) = 0;
    virtual void                    CleanupStaticLightingState( int nCount , DataCacheHandle_t *pColorMeshHandles ) = 0;
};

typedef unsigned short material_handle;

class material_system
{
public:
    material* find_material( const char* name , const char* texture_group , bool complain = true , const char* prefix = 0 )
    {
        using original = material * ( __thiscall* )( void* , const char* , const char* , bool , const char* );
        return globals::tools::get_virtualfn<84 , original>( this )( this , name , texture_group , complain , prefix );
    }

    material_handle first_material()
    {
        using original = material_handle( __thiscall* )( void* );
        return globals::tools::get_virtualfn<86 , original>( this )( this );
    }

    material_handle next_material( material_handle h )
    {
        using original = material_handle( __thiscall* )( void* , material_handle );
        return globals::tools::get_virtualfn<87 , original>( this )( this , h );
    }

    material_handle invalid_material()
    {
        using original = material_handle( __thiscall* )( void* );
        return globals::tools::get_virtualfn<88 , original>( this )( this );
    }

    material* get_material( material_handle h )
    {
        using original = material * ( __thiscall* )( void* , material_handle );
        return globals::tools::get_virtualfn<89 , original>( this )( this , h );
    }
};



