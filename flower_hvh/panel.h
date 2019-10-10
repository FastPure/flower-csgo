#pragma once
class panel_id
{
public:
    const char* get_panel( unsigned int panel_id )
    {
        using original = const char*( __thiscall* )( void* , unsigned int );
        return globals::tools::get_virtualfn<36 , original>( this )( this , panel_id );
    }
};

