#pragma once
typedef unsigned long crc32;

void init( crc32 *pulCRC );
void process_buffer_( crc32 *pulCRC , const void *p , int len );
void final( crc32 *pulCRC );

inline crc32 process_buffer( const void *p , int len )
{
    crc32 crc;

    init( &crc );
    process_buffer_( &crc , p , len );
    final( &crc );

    return crc;
}


class user_cmd
{
public:
    user_cmd()
    {
        memset( this , 0 , sizeof( *this ) );
    };
    virtual ~user_cmd()
    {
    };

    crc32 GetChecksum( void ) const
    {
        crc32 crc;
        init( &crc );

        process_buffer_( &crc , &command_number , sizeof( command_number ) );
        process_buffer_( &crc , &tick_count , sizeof( tick_count ) );
        process_buffer_( &crc , &view_angles , sizeof( view_angles ) );
        process_buffer_( &crc , &aim_direction , sizeof( aim_direction ) );
        process_buffer_( &crc , &foward , sizeof( foward ) );
        process_buffer_( &crc , &side , sizeof( side ) );
        process_buffer_( &crc , &up , sizeof( up ) );
        process_buffer_( &crc , &buttons , sizeof( buttons ) );
        process_buffer_( &crc , &impulse , sizeof( impulse ) );
        process_buffer_( &crc , &weapon_select , sizeof( weapon_select ) );
        process_buffer_( &crc , &weapon_subtype , sizeof( weapon_subtype ) );
        process_buffer_( &crc , &random_seed , sizeof( random_seed ) );
        process_buffer_( &crc , &mouse_x , sizeof( mouse_x ) );
        process_buffer_( &crc , &mouse_y , sizeof( mouse_y ) );

        final( &crc );
        return crc;
    }

    int     command_number;
    int     tick_count;
    vector  view_angles;
    vector  aim_direction;
    float   foward;
    float   side;
    float   up;
    int     buttons;
    char    impulse;
    int     weapon_select;
    int     weapon_subtype;
    int     random_seed;
    short   mouse_x;
    short   mouse_y;
    bool    predicted;
    char    pad_0x4C[ 0x18 ];
};

class verfified_user
{
public:
    user_cmd m_cmd;
    crc32  m_crc;
};

class input
{
public:
    char HUY[ 8 ];
    void*               pvftable;                     //0x00
    bool                m_fTrackIRAvailable;          //0x04
    bool                m_fMouseInitialized;          //0x05
    bool                m_fMouseActive;               //0x06
    bool                m_fJoystickAdvancedInit;      //0x07
    char                pad_0x08[ 0x2C ];               //0x08
    void*               m_pKeys;                      //0x34
    char                pad_0x38[ 0x64 ];               //0x38
    bool                m_fCameraInterceptingMouse;   //0x9C
    bool                m_fCameraInThirdPerson;       //0x9D
    bool                m_fCameraMovingWithMouse;     //0x9E
    vector              m_vecCameraOffset;            //0xA0
    bool                m_fCameraDistanceMove;        //0xAC
    int                 m_nCameraOldX;                //0xB0
    int                 m_nCameraOldY;                //0xB4
    int                 m_nCameraX;                   //0xB8
    int                 m_nCameraY;                   //0xBC
    bool                m_CameraIsOrthographic;       //0xC0
    vector              m_angPreviousViewAngles;      //0xC4
    vector              m_angPreviousViewAnglesTilt;  //0xD0
    float               m_flLastForwardMove;          //0xDC
    int                 m_nClearInputState;           //0xE0
    char                pad_0xE4[ 0x8 ];                //0xE4
    user_cmd*           m_pCommands;                  //0xEC
    verfified_user*   m_pVerifiedCommands;          //0xF0
};

class anim_state
{
public:
    char pad[ 4 ];
    char bUnknown; //0x4
    char pad2[ 91 ];
    void* pBaseEntity; //0x60
    void* pActiveWeapon; //0x64
    void* pLastActiveWeapon; //0x68
    float m_flLastClientSideAnimationUpdateTime; //0x6C
    int m_iLastClientSideAnimationUpdateFramecount; //0x70
    float m_flEyePitch; //0x74
    float m_flEyeYaw; //0x78
    float m_flPitch; //0x7C
    float m_flGoalFeetYaw; //0x80
    float m_flCurrentFeetYaw; //0x84
    float m_flCurrentTorsoYaw; //0x88
    float m_flUnknownVelocityLean; //0x8C //changes when moving/jumping/hitting ground
    float m_flLeanAmount; //0x90
    char pad4[ 4 ]; //NaN
    float m_flFeetCycle; //0x98 0 to 1
    float m_flFeetYawRate; //0x9C 0 to 1
    float m_fUnknown2;
    float m_fDuckAmount; //0xA4
    float m_fLandingDuckAdditiveSomething; //0xA8
    float m_fUnknown3; //0xAC
    vec_t m_vOrigin; //0xB0, 0xB4, 0xB8
    vec_t m_vLastOrigin; //0xBC, 0xC0, 0xC4
    float m_vVelocityX; //0xC8
    float m_vVelocityY; //0xCC
    char pad5[ 4 ];
    float m_flUnknownFloat1; //0xD4 Affected by movement and direction
    char pad6[ 8 ];
    float m_flUnknownFloat2; //0xE0 //from -1 to 1 when moving and affected by direction
    float m_flUnknownFloat3; //0xE4 //from -1 to 1 when moving and affected by direction
    float m_unknown; //0xE8
    float speed_2d; //0xEC
    float flUpVelocity; //0xF0
    float m_flSpeedNormalized; //0xF4 //from 0 to 1
    float m_flFeetSpeedForwardsOrSideWays; //0xF8 //from 0 to 2. something  is 1 when walking, 2.something when running, 0.653 when crouch walking
    float m_flFeetSpeedUnknownForwardOrSideways; //0xFC //from 0 to 3. something
    float m_flTimeSinceStartedMoving; //0x100
    float m_flTimeSinceStoppedMoving; //0x104
    unsigned char m_bOnGround; //0x108
    int8_t m_bInHitGroundAnimation; //0x109
    char pad7[ 10 ];
    float m_flLastOriginZ; //0x114
    float m_flHeadHeightOrOffsetFromHittingGroundAnimation; //0x118 from 0 to 1, is 1 when standing
    float m_flStopToFullRunningFraction; //0x11C from 0 to 1, doesnt change when walking or crouching, only running
    char pad8[ 4 ]; //NaN
    float m_flUnknownFraction; //0x124 affected while jumping and running, or when just jumping, 0 to 1
    char pad9[ 4 ]; //NaN
    float m_flUnknown3;
    char pad10[ 528 ];
};

