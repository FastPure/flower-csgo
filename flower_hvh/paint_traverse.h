#pragma once
#include "drawing.h"
#include "esp.h"
#include "others.h"

namespace paint_traverse
{
    using prototype_paint_traverse = void( __thiscall* )( void* , unsigned int , bool , bool );
    prototype_paint_traverse original_paint_traverse = nullptr;

    std::unique_ptr<vmt_hook> hook_paint;

    bool hooked = false;
    static unsigned int panel_id = 0;

    auto init()
    {
        globals::menu::fonts::esp = flower_sdk::p_surface->create_font();
        flower_sdk::p_surface->set_font_style( globals::menu::fonts::esp , "Small Fonts" , 12 , 400 , 0 , 0 , flower_sdk::p_surface->outline );
    }

    void __stdcall hook_paint_traverse( unsigned int current_panel , bool force_repaint , bool allow_force )
    {
        if ( hooked == false )
        {
            std::cout << "\npaint traverse hooked.";
            hooked = true;
        }

        if ( globals::functions::visuals::others::others_enable == true && 
            globals::functions::visuals::others::no_scope == true  )
        {
            if ( strcmp( flower_sdk::p_panel->get_panel( current_panel ) , "HudZoom" ) == 0 )
                return;
        }

        if ( !panel_id )
        {
            if ( strcmp( flower_sdk::p_panel->get_panel( current_panel ) , "FocusOverlayPanel" ) == 0 )
                panel_id = current_panel;
        }

        if ( panel_id && current_panel == panel_id )
        {
            if ( flower_sdk::p_engine->is_connected() == false )
            {
                send_datagram::hooked = false;
                globals::functions::visuals::others::should_update_skye = true;
                globals::functions::visuals::others::should_update_event_bullet_tracer = true;
                globals::functions::visuals::others::should_update_event_hitmarker = true;
                return;
            }

            if( globals::functions::esp::esp_enable == true )
                esp::init();
    
            if ( globals::functions::visuals::others::others_enable == true )
                others::init();
                      
        }

        return original_paint_traverse( flower_sdk::p_panel , current_panel , force_repaint , allow_force );
    }
}