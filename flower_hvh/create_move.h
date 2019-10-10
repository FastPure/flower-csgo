#pragma once
#include "fixes.h"
#include "aim.h"

namespace create_move
{
    using prototype_create_move = bool( __thiscall* )( void* , float , user_cmd * );
    prototype_create_move original_create_move = nullptr;

    std::unique_ptr<vmt_hook> hook_create;

    bool hooked = false;

    bool __stdcall hook_create_move( float time , user_cmd * cmd )
    {
        if ( !cmd->command_number )
            return  original_create_move( flower_sdk::p_client_mode , time , cmd );

        if ( hooked == false )
        {
            hooked = true;
            std::cout << "\ncreate move hooked";
        }

        csplayer * local = flower_sdk::p_entity_list->get_entity( flower_sdk::p_engine->get_local_player() );

        if ( !local )
            return true;

        auto weapon = flower_sdk::p_entity_list->get_entity( local->get_active_wep_index() );
        if ( !weapon )
            return true;

        const weapon_struct * wep_info = weapon->get_weapon_info();
        if ( !wep_info )
            return true;

        if ( globals::functions::move::aim_enable == false )
            return true;
        
        uintptr_t* pointer; __asm { MOV pointer , EBP }
        bool& send_packet = *( bool* ) ( *pointer - 0x1C );

        globals::functions::move::velocity = local->get_velocity();

        move::init( send_packet , cmd , local , wep_info , weapon );

        fixes::clamp_and_normalize( cmd->view_angles );

        fixes::fix_slide( cmd );

        fixes::fix_move( cmd );
        
        globals::functions::move::last_angle = cmd->view_angles;

        return false;
    }
}