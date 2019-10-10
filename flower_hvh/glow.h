#pragma once
namespace glow
{
    auto init()
    {
            csplayer * local = flower_sdk::p_entity_list->get_entity( flower_sdk::p_engine->get_local_player() );

            if ( !local )
                return 0;

            for ( auto i = 1; i < flower_sdk::p_glow->size; i++ )
            {
                auto glow_object = &flower_sdk::p_glow->glow_def_[ i ];

                csplayer * entity = glow_object->entity;

                if ( !entity || glow_object->unused() )
                    continue;

                if ( globals::functions::visuals::glow::glow_entities_to_glow[ 0 ] == true )
                {
                    if ( entity->get_client_class()->class_id == class_ids::CCSPlayer  )
                    {
                        if ( globals::functions::visuals::glow::glow_team == false )
                        {
                            if ( entity->get_team() == local->get_team() )
                                continue;
                        }

                        if ( esp::is_visible( local , entity ) )
                        {
                            glow_object->colors = vector( 1, 
                                                          0,
                                                          1);

                            glow_object->a = glow_sytles::sizes::medium;

                            glow_object->style = glow_sytles::hot;


                            glow_object->occluded = true;
                            glow_object->unoccluded = false;
                        }
                        else
                        {
                            glow_object->colors = vector( 1, 
                                                          1, 
                                                          1);

                            glow_object->a = glow_sytles::sizes::pixel;

                            glow_object->style = glow_sytles::regular;


                            glow_object->occluded = true;
                            glow_object->unoccluded = false;
                        }

                    }
                }

                if ( globals::functions::visuals::glow::glow_entities_to_glow[ 1 ] == true )
                {
                    if ( entity->get_client_class()->class_id == class_ids::CPlantedC4 )
                    {
                        if ( esp::is_visible( local , entity ) )
                        {
                            glow_object->colors = vector( 0 ,
                                                          1 ,
                                                          0 );

                            glow_object->a = glow_sytles::sizes::medium;

                            glow_object->style = glow_sytles::outline;


                            glow_object->occluded = true;
                            glow_object->unoccluded = false;
                        }
                        else
                        {
                            glow_object->colors = vector( 1 ,
                                                          1 ,
                                                          1 );

                            glow_object->a = glow_sytles::sizes::pixel;

                            glow_object->style = glow_sytles::regular;


                            glow_object->occluded = true;
                            glow_object->unoccluded = false;
                        }
                    }
                }

                if ( globals::functions::visuals::glow::glow_entities_to_glow[ 2 ] == true )
                {
                    if ( entity->get_client_class()->class_id == class_ids::CChicken )
                    {
                        if ( esp::is_visible( local , entity ) )
                        {
                            glow_object->colors = vector( 0 ,
                                                          1 ,
                                                          0 );

                            glow_object->a = glow_sytles::sizes::medium;

                            glow_object->style = glow_sytles::outline;


                            glow_object->occluded = true;
                            glow_object->unoccluded = false;
                        }
                        else
                        {
                            glow_object->colors = vector( 1 ,
                                                          1 ,
                                                          1 );

                            glow_object->a = glow_sytles::sizes::pixel;

                            glow_object->style = glow_sytles::regular;


                            glow_object->occluded = true;
                            glow_object->unoccluded = false;
                        }
                    }
                }

                if ( globals::functions::visuals::glow::glow_entities_to_glow[ 3 ] == true )
                {
                    if ( entity->get_client_class()->class_id == class_ids::CDrone || class_ids::CDronegun )
                    {
                        if ( esp::is_visible( local , entity ) )
                        {
                            glow_object->colors = vector( 0 ,
                                                          1 ,
                                                          0 );

                            glow_object->a = glow_sytles::sizes::medium;

                            glow_object->style = glow_sytles::outline;


                            glow_object->occluded = true;
                            glow_object->unoccluded = false;
                        }
                        else
                        {
                            glow_object->colors = vector( 1 ,
                                                          1 ,
                                                          1 );

                            glow_object->a = glow_sytles::sizes::pixel;

                            glow_object->style = glow_sytles::regular;


                            glow_object->occluded = true;
                            glow_object->unoccluded = false;
                        }
                    }
                }
            }
  
        return 1;
    }
}