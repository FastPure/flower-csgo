#pragma once
#include "glow.h"
#include "chams.h"

namespace post_screen_effects
{
    using prototype_post_screen_effects = int( __thiscall* )( void *, int );
    prototype_post_screen_effects original_post_screen_effects = nullptr;

    std::unique_ptr<vmt_hook> hook_post;

    bool hooked = false;
    int __fastcall hook_post_screen_effects( void * this_ptr , void *edx , int arg )
    {
        if ( hooked == false )
        {
            std::cout << "\npost screen effects hooked.";

            hooked = true;
        }

        if ( flower_sdk::p_engine->is_connected() == false )
            return 0;

        if ( globals::functions::visuals::glow::glow_enable == true )
            glow::init();

        if ( globals::functions::visuals::chams::chams_enable == true )
            chams::init();

        if ( globals::functions::visuals::others::no_smoke == true )
            chams::no_smoke();

        return original_post_screen_effects( this_ptr , arg );
    }
}