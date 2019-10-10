#pragma once
class debug_overlay
{
public:
    auto world_to_screen( vector& in , vector& out )
    {
        using original = int( __thiscall* )( void* , vector& , vector& );
        return globals::tools::get_virtualfn<13 , original>( this )( this , in , out );
    }
};