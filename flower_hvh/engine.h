#pragma once
struct player_info
{
    unsigned __int64 unknown;
    unsigned __int64 xuid;

    char name[ 32 ];
    char pad_1[ 96 ];

    int user_id;
    char guid[ 32 + 1 ];

    __int32 friends_id;
    char friends_name[ 32 ];

    bool is_bot;
    bool is_hltv;

    unsigned long custom_files[ 4 ];
    unsigned char downloaded_files;

    char pad_2[ 304 ];
};

class engine
{
public:
    auto get_screen_size( uint32_t& width , uint32_t& height )
    {
        using original = void( __thiscall* )( void* , uint32_t& , uint32_t& );
        return globals::tools::get_virtualfn<5 , original>( this )( this , width , height );
    }

    auto get_player_info( uint32_t index , player_info * info )
    {
        using original = void( __thiscall* )( void* , int , player_info* );
        return globals::tools::get_virtualfn<8 , original>( this )( this , index , info );
    }

    auto get_player_id( int userID )
    {
        using original = int( __thiscall* )( void* , int );
        return globals::tools::get_virtualfn<9 , original>( this )( this , userID );
    }

    auto get_local_player()
    {
        using original = uint32_t( __thiscall* )( void* );
        return globals::tools::get_virtualfn<12 , original>( this )( this );
    }

    auto get_view_angles( vector& angle )
    {
        using original = void( __thiscall* )( void* , vector& );
        return globals::tools::get_virtualfn<18 , original>( this )( this , angle );
    }

    auto set_view_angles( vector& angles )
    {
        using original = void( __thiscall* )( void* , vector& );
        return globals::tools::get_virtualfn<19 , original>( this )( this , angles );
    }

    auto get_max_clients()
    {
        using original = uint32_t( __thiscall * )( void* );
        return globals::tools::get_virtualfn < 20 , original>( this )( this );
    }

    auto is_in_game()
    {
        using original = bool( __thiscall* )( void* );
        return globals::tools::get_virtualfn<26 , original>( this )( this );
    }

    auto is_connected()
    {
        using original = bool( __thiscall* )( void* );
        return globals::tools::get_virtualfn<27 , original>( this )( this );
    }

    auto execute_cmd( const char* cmd , char flag )
    {
        using original = void( __thiscall* )( void* , const char * , char );
        return globals::tools::get_virtualfn<114 , original>( this )( this , cmd , flag );
    }
};