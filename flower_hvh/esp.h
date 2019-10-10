#pragma once
namespace esp
{
    std::string fix_item_name( std::string name )
    {
        if ( name[ 0 ] == 'C' )
            name.erase( name.begin() );

        auto looking_for_string = name.find( "Weapon" );
        if ( looking_for_string != std::string::npos )
            name.erase( name.begin() + looking_for_string , name.begin() + looking_for_string + 6 );

        return name;
    }

    bool is_visible( csplayer * local , csplayer * player )
    {
        trace_ tr;
        ray_ ray;
        trace_filter_ filter;
        filter.skip = local;

        ray.init( local->get_eye_pos() , player->get_bone_pos( 8 ) );
        flower_sdk::p_trace->trace_ray( ray , MASK_SHOT , &filter , &tr );

        return  tr.fraction > 0.97f;
    }

    auto init()
    {
        csplayer * local = flower_sdk::p_entity_list->get_entity( flower_sdk::p_engine->get_local_player() );

        if ( !local )
            return;

        for ( uint32_t i = 1; i < flower_sdk::p_entity_list->get_highest_entity_index(); i++ )
        {
            csplayer * player = flower_sdk::p_entity_list->get_entity( i );

            if ( !player )
                continue;

            if ( player == local )
                continue;

            if ( globals::functions::esp::esp_team == false )
            {
                if ( player->get_team() == local->get_team() )
                    continue;
            }

            if ( player->get_dormant() == true )
                continue;

            if ( player->get_health() == 0 )
                continue;

            vector min , max_;
            player->render_bounds( min , max_ );

            vector pos , pos3d , top , top3d;

            pos3d = player->get_abs_origin() - vector( 0 , 0 , 10 );
            top3d = pos3d + vector( 0 , 0 , max_.z + 10 );

            if ( ( flower_sdk::p_debug_overlay->world_to_screen( pos3d , pos ) != 1 ) &&
                ( flower_sdk::p_debug_overlay->world_to_screen( top3d , top ) != 1 ) )
            {
                auto height = ( pos.y - top.y );
                auto width = height / 1.2;

                player_info info;
                flower_sdk::p_engine->get_player_info( i , &info );

                std::cout << is_visible( local , player ) << "\n";

                if ( globals::functions::esp::esp_box == true )
                {
                    if ( is_visible( local , player ) == true )
                    {
                        drawing::draw_outline_box( ( pos.x - width / 2 ) , top.y , ( pos.x - width / 2 ) + width , top.y + height ,
                                                   0 , 255 , 0 , 255 );
                    }
                    else
                    {
                        drawing::draw_outline_box( ( pos.x - width / 2 ) , top.y , ( pos.x - width / 2 ) + width , top.y + height ,
                                                   255 , 255 , 255 , 255 );
                    }
                }

                if ( globals::functions::esp::esp_name == true )
                {
                        drawing::draw_complex_text( ( ( pos.x + width / 150 ) - 8 ) ,
                            ( top.y - 15 ) , 255 , 255 , 255 , 255 ,
                                                    globals::menu::fonts::esp , "%s" , info.name );
                }

                if ( globals::functions::esp::esp_armor == true )
                {
                    uint32_t current_armor = player->get_armor();
                    uint32_t hp = height - ( ( height * current_armor ) / 100 );

                    drawing::draw_outline_box( ( ( pos.x + width / 1.90 ) - 5 ) ,
                                             top.y - 1 , ( ( pos.x + width / 1.90 ) - 3 ) ,
                                             top.y + height + 2
                                             , 0 , 0 , 0 , 150 );

                    drawing::draw_line( ( ( pos.x + width / 1.90 ) - 5 ) ,
                                        top.y + hp , ( ( pos.x + width / 1.90 ) - 5 ) , top.y + height ,
                                        0 , 135 ,
                                        255 , 255 );
                }

                if ( globals::functions::esp::esp_health == true )
                {
                    uint32_t current_health = player->get_health();
                    uint32_t hp = height - ( ( height * current_health ) / 100 );

                    drawing::draw_outline_box( ( ( pos.x - width / 2 ) - 5 ) ,
                                             top.y - 1 , ( ( pos.x - width / 2 ) - 3 ) ,
                                             top.y + height + 2
                                             , 0 , 0 , 0 , 150 );

                    if ( current_health >= 75 )
                        drawing::draw_line( ( ( pos.x - width / 2 ) - 5 ) ,
                                            top.y + hp , ( ( pos.x - width / 2 ) - 5 )
                                            , top.y + height ,
                                            0 , 255 , 0 , 255 );
                    else if ( current_health >= 35 )
                        drawing::draw_line( ( ( pos.x - width / 2 ) - 5 ) ,
                                            top.y + hp , ( ( pos.x - width / 2 ) - 5 )
                                            , top.y + height ,
                                            240 , 255 , 0 , 255 );
                    else
                        drawing::draw_line( ( ( pos.x - width / 2 ) - 5 ) ,
                                            top.y + hp , ( ( pos.x - width / 2 ) - 5 )
                                            , top.y + height ,
                                            255 , 0 , 0 , 255 );
                }

                if ( globals::functions::esp::esp_line == true )
                {
                    uint32_t w = 0 , h = 0;

                    flower_sdk::p_engine->get_screen_size( w , h );
                    vector current( ( w / 2 ) , h - 1 , 0 );

                    if ( is_visible( local , player ) == true )
                        drawing::draw_line( current.x , current.y , pos.x , pos.y , 0 , 255 , 0 , 255 );
                    else
                        drawing::draw_line( current.x , current.y , pos.x , pos.y , 255 , 255 , 255 , 255 );
                }

                if ( globals::functions::esp::esp_current_wep_name == true )
                {
                    weapon_base * wep_cast = ( weapon_base* ) player;
                    if ( !wep_cast )
                        continue;

                    auto weapon = flower_sdk::p_entity_list->get_entity( player->get_active_wep_index() );
                    if ( !weapon ) 
                        continue;

                    std::string name = fix_item_name( weapon->get_client_class()->network_name );

                    drawing::draw_complex_text( ( ( pos.x - width / 2 ) ) ,
                                                pos.y , 255 , 255 , 255 , 255 ,
                                                globals::menu::fonts::esp , name.c_str() );
                }

                if ( globals::functions::esp::esp_skeleton == true )
                {
                    studiohdr_t * p_studio = flower_sdk::p_model->get_studio_model( player->get_model() );

                    if ( !p_studio )
                        continue;

                    vector parent , child , screen_parent , screen_child;

                    for ( uint32_t i = 0; i < p_studio->numbones; i++ )
                    {
                        mstudiobone_t * bone = p_studio->get_bone( i );

                        if ( bone && ( bone->flags & 0x00000100 ) && ( bone->parent != -1 ) )
                        {
                            child = player->get_bone_pos( i );
                            parent = player->get_bone_pos( bone->parent );

                            if ( ( flower_sdk::p_debug_overlay->world_to_screen( parent , screen_parent ) != 1 ) &&
                                ( flower_sdk::p_debug_overlay->world_to_screen( child , screen_child ) != 1 ) )
                                drawing::draw_line( screen_parent[ 0 ] , screen_parent[ 1 ] , screen_child[ 0 ] , screen_child[ 1 ] ,
                                                    255 , 255 , 255 , 255 );
                        }
                    }
                }

            }
        }
    }
}