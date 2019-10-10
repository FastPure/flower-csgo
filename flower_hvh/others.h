#pragma once
#include "events.h"

namespace others
{
    auto init()
    {
        csplayer * local = flower_sdk::p_entity_list->get_entity( flower_sdk::p_engine->get_local_player() );

        if ( !local )
            return;

        if ( globals::functions::visuals::others::night_mode == true )
        {
            if ( globals::functions::visuals::others::should_update_skye == true )
            {
                static auto draw_prop = flower_sdk::p_cvar->find_var( "r_drawspecificstaticprop" );
                draw_prop->flags &= ~( 1 << 14 );
                draw_prop->set_value( 0 );

                static auto sky = flower_sdk::p_cvar->find_var( "sv_skyname" );
                sky->flags &= ~( 1 << 14 );

                for ( material_handle i = flower_sdk::p_material_system->first_material();
                      i != flower_sdk::p_material_system->invalid_material(); i = flower_sdk::p_material_system->next_material( i ) )
                {
                    material * temp_material = flower_sdk::p_material_system->get_material( i );

                    if ( !temp_material )
                        continue;

                    if ( strstr( temp_material->GetTextureGroupName() , "Model" ) )
                    {
                        temp_material->color_modulate( 0.60 , 0.60 , 0.60 );
                    }

                    if ( strstr( temp_material->GetTextureGroupName() , "World" ) )
                    {
                        sky->set_value( "sky_csgo_night02" );
                        temp_material->set_material_flag( MATERIAL_VAR_TRANSLUCENT , false );
                        temp_material->color_modulate( 0.1 , 0.1 , 0.1 );
                    }

                    if ( strstr( temp_material->GetTextureGroupName() , "StaticProp" ) )
                    {
                        temp_material->color_modulate( 0.3 , 0.3 , 0.3 );
                    }
                }
                globals::functions::visuals::others::should_update_skye = false;
            }
        }

        if ( globals::functions::visuals::others::no_flash == true )
        {
            *local->get_flash_duration() = 0.f;
        }

        if ( globals::functions::visuals::others::no_scope == true )
        {
            if ( local->is_scoped() == true )
            {
                static auto mat_postprocess = flower_sdk::p_cvar->find_var( "mat_postprocess_enable" );
                mat_postprocess->flags &= ~( 1 << 14 );
                mat_postprocess->set_value( 0 );

                uint32_t width , height;

                flower_sdk::p_engine->get_screen_size( width , height );
                drawing::draw_line( width / 2 , 0 , width / 2 , height , 0 , 0 , 0 , 255 );
                drawing::draw_line( 0 , height / 2 , width , height / 2 , 0 , 0 , 0 , 255 );
            }
        }

        if ( globals::functions::visuals::others::no_smoke == true )
        {
            *reinterpret_cast< uint32_t * >( globals::game_resources::smoke_cout ) = 0;
        }

        if ( globals::functions::visuals::others::show_impact == true )
        {
            static auto listen_bullet_tracers = flower_sdk::p_cvar->find_var( "sv_showimpacts" );
            listen_bullet_tracers->flags &= ~( 1 << 14 );
            listen_bullet_tracers->set_value( 1 );

            static auto impacts_time = flower_sdk::p_cvar->find_var( "sv_showimpacts_time" );
            impacts_time->flags &= ~( 1 << 14 );
            impacts_time->set_value( 2 );           
        }
        else
        {
            static auto listen_bullet_tracers = flower_sdk::p_cvar->find_var( "sv_showimpacts" );
            listen_bullet_tracers->flags &= ~( 1 << 14 );
            listen_bullet_tracers->set_value( 0 );

            static auto impacts_time = flower_sdk::p_cvar->find_var( "sv_showimpacts_time" );
            impacts_time->flags &= ~( 1 << 14 );
            impacts_time->set_value( 0 );
        }

        if ( globals::functions::visuals::others::bullet_tracer == true )
        {        
            if ( globals::functions::visuals::others::should_update_event_bullet_tracer == true )
            {
                register_event( events::bullet_impacts , &events::listen_bullet_tracers , "bullet_impact" , false );
                globals::functions::visuals::others::should_update_event_bullet_tracer = false;
            }

            for ( uint32_t i = 0; i < tracer_logs.size(); i++ )
            {
                auto * shooter = flower_sdk::p_entity_list->get_entity( flower_sdk::p_engine->get_player_id( tracer_logs[ i ].user_id ) );

                if ( !shooter )
                    return;

                if ( shooter == local )
                {
                    if ( globals::functions::visuals::others::bullet_tracer_random == true )
                    {
                        std::default_random_engine random_number( std::random_device {}( ) );
                        std::uniform_real_distribution<double> r( 0 , 255 ) ,
                            g( 0 , 255 ) , b( 0 , 255 ) ,
                            style( 2 , 4 );

                        std::uniform_real_distribution<float> amplitude( 0 , 20.f );

                        const double color_r = r( random_number ) ,
                            color_g = g( random_number ),
                            color_b = b( random_number ),
                            random_style = style( random_number );

                        const float random_amplitude = amplitude( random_number );

                        draw_beam( tracer_logs[ i ].start , tracer_logs[ i ].position ,
                                   random_style , random_amplitude ,
                                   color_r , color_g , color_b , 255 );

                        tracer_logs.erase( tracer_logs.begin() + i );
                    }
                    else
                    {
                        draw_beam( tracer_logs[ i ].start , tracer_logs[ i ].position ,
                                   3 , 10.f , 255 , 255 , 0 , 255 );
                        tracer_logs.erase( tracer_logs.begin() + i );
                    }
                }
            }
        }

        if ( globals::functions::visuals::others::listen_hitmarkers == true )
        {
            if ( globals::functions::visuals::others::should_update_event_hitmarker == true )
            {
                register_event( events::player_hurt , &events::listen_hitmarkers , "player_hurt" , false );
                globals::functions::visuals::others::should_update_event_hitmarker = false;
            }

            auto curtime = flower_sdk::p_globals_var_base->curtime;
            auto lineSize = 8;
            if ( events::hurt_time + 0.25f >= curtime )
            {
                uint32_t screen_size_x , screen_size_y ,
                    screen_center_x , screen_center_y;

                flower_sdk::p_engine->get_screen_size( screen_size_x , screen_size_y );

                screen_center_x = screen_size_x / 2;
                screen_center_y = screen_size_y / 2;

                drawing::draw_line( screen_center_x - lineSize , screen_center_y - lineSize ,
                                    screen_center_x - ( lineSize / 4 ) , screen_center_y - ( lineSize / 4 ) ,
                                    255 , 255 , 255 , 255 );

                drawing::draw_line( screen_center_x - lineSize , screen_center_y + lineSize ,
                                    screen_center_x - ( lineSize / 4 ) , screen_center_y + ( lineSize / 4 ) ,
                                    255 , 255 , 255 , 255 );

                drawing::draw_line( screen_center_x + lineSize , screen_center_y + lineSize ,
                                    screen_center_x + ( lineSize / 4 ) , screen_center_y + ( lineSize / 4 ) ,
                                    255 , 255 , 255 , 255 );

                drawing::draw_line( screen_center_x + lineSize , screen_center_y - lineSize ,
                                    screen_center_x + ( lineSize / 4 ) , screen_center_y - ( lineSize / 4 ) ,
                                    255 , 255 , 255 , 255 );
            }
        }

        if ( globals::functions::visuals::others::third_person == true )
        {
            if ( local->get_health() == 0 )
                return;

            if ( GetKeyState( VK_XBUTTON2 ) && globals::functions::visuals::others::was_in_third_person == false )
            {
                static auto sv_cheats = flower_sdk::p_cvar->find_var( "sv_cheats" );
                sv_cheats->flags &= ~( 1 << 14 );
                sv_cheats->set_value( 1 );

                flower_sdk::p_engine->execute_cmd( "thirdperson" , 0 );

                globals::functions::visuals::others::was_in_third_person = true;
            }
            if ( GetKeyState( VK_XBUTTON1 ) && globals::functions::visuals::others::was_in_third_person == true )
            {
                static auto sv_cheats = flower_sdk::p_cvar->find_var( "sv_cheats" );
                sv_cheats->flags &= ~( 1 << 14 );
                sv_cheats->set_value( 1 );

                flower_sdk::p_engine->execute_cmd( "firstperson" , 0 );

                globals::functions::visuals::others::was_in_third_person = false;
            }
        }
    }
}