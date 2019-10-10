#pragma once
class entity_list
{
public:
    csplayer * get_entity( uint32_t i )
    {
        using original = csplayer * ( __thiscall* )( void* , uint32_t );
        return globals::tools::get_virtualfn<3 , original>( this )( this , i );
    }

    auto get_highest_entity_index()
    {
        using original = int ( __thiscall* )( void*  );
        return globals::tools::get_virtualfn<6 , original>( this )( this );
    }

    csplayer * get_entity_handle( HANDLE i )
    {
        using original = csplayer * ( __thiscall* )( void* , void* );
        return globals::tools::get_virtualfn<7 , original>( this )( this , i );
    }
};

