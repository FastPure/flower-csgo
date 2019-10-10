#pragma once
namespace chams
{
    material * my_material = nullptr;

    auto override_material( const char * name , unsigned __int8 r , unsigned __int8 g , unsigned __int8 b , float a )
    {
        material * temp_material = nullptr;

        my_material = flower_sdk::p_material_system->find_material( name , nullptr , false , 0 );

        temp_material = my_material;

        temp_material->color_modulate( r , g , b );
        temp_material->alpha_modulate( a );

        temp_material->set_material_flag( MATERIAL_VAR_IGNOREZ , true );


        flower_sdk::p_model_render->force_material_override( temp_material );
    }

    auto no_smoke()
    {
        static std::vector< const char* > smoke_materials = {
    "particle/vistasmokev1/vistasmokev1_smokegrenade",
    "particle/vistasmokev1/vistasmokev1_emods",
    "particle/vistasmokev1/vistasmokev1_emods_impactdust",
    "particle/vistasmokev1/vistasmokev1_fire",
        };

        for ( auto matName : smoke_materials )
        {
            material * temp_material = flower_sdk::p_material_system->find_material( matName , "Other textures" );
            temp_material->set_material_flag( MATERIAL_VAR_NO_DRAW , true );
            flower_sdk::p_model_render->force_material_override( temp_material );
        }
    }

    auto init( )
    {
        csplayer * local = flower_sdk::p_entity_list->get_entity( flower_sdk::p_engine->get_local_player() );

        if ( !local )
            return;

        for ( uint32_t i = 1; i < flower_sdk::p_engine->get_max_clients(); i++ )
        {
            auto player = flower_sdk::p_entity_list->get_entity( i );

            if ( !player )
                continue;

            if ( globals::functions::visuals::chams::chams_team == false )
            {
                if ( player->get_team() == local->get_team() )
                    continue;
            }

            if ( globals::functions::visuals::chams::chams_types == 0 )
            {
                if ( esp::is_visible( local , player ) )
                {
                    override_material( "models/player/ct_fbi/ct_fbi_glass" ,
                                       255 , 50 , 0 , 1 );
                    player->draw_model( 0x1 , player->get_model_instance() );
                    flower_sdk::p_model_render->force_material_override( nullptr );
                }
                else
                {
                    override_material( "models/player/ct_fbi/ct_fbi_glass" ,
                                       0 , 35 , 255 , 1 );
                    player->draw_model( 0x1 , player->get_model_instance() );
                    flower_sdk::p_model_render->force_material_override( nullptr );
                }
            }

            if ( globals::functions::visuals::chams::chams_types == 1 )
            {
                if ( esp::is_visible( local , player ) )
                {
                    override_material( "models/inventory_items/cologne_prediction/cologne_prediction_glass" , 
                                       255 , 50 , 0 , 1 );
                    player->draw_model( 0x1 , player->get_model_instance() );
                    flower_sdk::p_model_render->force_material_override( nullptr );
                }
                else
                {
                    override_material( "models/inventory_items/cologne_prediction/cologne_prediction_glass" , 
                                       0, 35, 255, 1);
                    player->draw_model( 0x1 , player->get_model_instance() );
                    flower_sdk::p_model_render->force_material_override( nullptr );
                }
            }

            if ( globals::functions::visuals::chams::chams_types == 2 )
            {
                override_material( "models/inventory_items/dogtags/dogtags_outline" ,
                                   0 , 0 , 255 , 1 );
                player->draw_model( 0x1 , player->get_model_instance() );
                flower_sdk::p_model_render->force_material_override( nullptr );
            }

            if ( globals::functions::visuals::chams::chams_server == true  )
            {
                auto original_angle = local->get_eye_angle();
                local->set_angle( vector( 0 , globals::functions::move::last_angle.y , 0 ) );
                override_material( "models/player/ct_fbi/ct_fbi_glass" , 255 , 255 , 255 , 1 );
                local->draw_model( 0x1 , local->get_model_instance() );
                flower_sdk::p_model_render->force_material_override( nullptr );
                local->set_angle( original_angle );             
            }
        }
    }
}