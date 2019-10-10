#pragma once
namespace move
{
    namespace backtrack
    {
#define tick_interval			(flower_sdk::p_globals_var_base->interval_per_tick)
#define time_to_tick( time )		( (int)( 0.5f + (float)(time) / tick_interval ) )

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

        namespace legit
        {
            struct backtrack_data
            {
                float simulation_time;
                vector hitbox_pos;
            };
            backtrack_data hitbox_position[ 32 ][ 12 ];

            auto init( user_cmd * cmd , csplayer * local )
            {
                for ( int i = 1; i < flower_sdk::p_entity_list->get_highest_entity_index(); i++ )
                {
                    csplayer * player = flower_sdk::p_entity_list->get_entity( i );

                    if ( !player )
                        continue;

                    if ( player == local )
                        continue;

                    if ( player->get_dormant() == true )
                        continue;

                    if ( player->get_health() == 0 )
                        continue;

                    int target_index = -1;
                    float max_possible_fov = FLT_MAX;

                    float sim_time = player->get_simulation_time();

                    vector hitbox_pos = player->get_bone_pos( 8 );

                    hitbox_position[ i ][ cmd->command_number % 13 ] = backtrack_data { sim_time, hitbox_pos };
                    vector view_direction = fixes::angle_to_vector( cmd->view_angles + ( local->get_aim_punch() * 2.f ) );
                    float fov = fixes::distance_point_to_line( hitbox_pos , local->get_eye_pos() , view_direction );

                    if ( max_possible_fov > fov )
                    {
                        max_possible_fov = fov;
                        target_index = i;
                    }

                    float best_tagert_time;
                    if ( target_index != -1 && is_visible( local , player ) )
                    {
                        float temp_max_fov = FLT_MAX;
                        vector view_direction = fixes::angle_to_vector( cmd->view_angles + ( local->get_aim_punch() * 2.f ) );

                        for ( int t = 0; t < 12; ++t )
                        {
                            float temp_fov =
                                fixes::distance_point_to_line( hitbox_position[ target_index ][ t ].hitbox_pos ,
                                                               local->get_eye_pos() , view_direction );

                            if ( temp_max_fov > temp_fov &&
                                 hitbox_position[ target_index ][ t ].simulation_time > local->get_simulation_time() - 1 )
                            {
                                temp_max_fov = temp_fov;
                                best_tagert_time = hitbox_position[ target_index ][ t ].simulation_time;
                            }
                        }
                    }
                    cmd->tick_count = time_to_tick( best_tagert_time );
                }
            }
        }

        namespace rage
        {
            struct sequence
            {
                sequence( int instate , int out_state , int seqnr , float real_time )
                {
                    state = instate;
                    out_state_ = out_state;
                    sequencenr = seqnr;
                    real_time_ = real_time;
                }
                int state;
                int out_state_;
                int sequencenr;
                float real_time_;
            };
            int last_incoming_sequence = 0;
            std::deque<sequence> sequence_records;

            struct backtrack_data
            {
                float simulation_time;
                vector hitbox_pos;
            };
            backtrack_data hitbox_position[ 32 ][ 24 ];

            auto init( user_cmd * cmd , csplayer * local )
            {
                if ( send_datagram::hooked == false )
                {
                    auto client_state = *reinterpret_cast< uintptr_t* >( uintptr_t( GetModuleHandle( "engine.dll" ) ) + 0x58BCFC );

                    if ( client_state )
                    {
                        auto net_chan = *reinterpret_cast< uintptr_t* >( client_state + globals::game_resources::net_chan );
                        if ( net_chan )
                        {
                            send_datagram::hooked = true;
                            send_datagram::send_datagram = std::make_unique<vmt_hook>( ( void*** ) net_chan );
                            send_datagram::original_send_datagram =
                                send_datagram::send_datagram->hook<send_datagram::prototype_send_datagram>
                                ( 46 , send_datagram::hook_send_datagram );
                        }
                    }
                }

                for ( int i = 1; i < flower_sdk::p_entity_list->get_highest_entity_index(); i++ )
                {
                    csplayer * player = flower_sdk::p_entity_list->get_entity( i );

                    if ( !player )
                        continue;

                    if ( player == local )
                        continue;

                    if ( player->get_dormant() == true )
                        continue;

                    if ( player->get_health() == 0 )
                        continue;
                    int target_index = -1;
                    float max_possible_fov = FLT_MAX;

                    float sim_time = player->get_simulation_time();

                    vector hitbox_pos = player->get_bone_pos( 8 );

                    hitbox_position[ i ][ cmd->command_number % 25 ] = backtrack_data { sim_time, hitbox_pos };
                    vector view_direction = fixes::angle_to_vector( cmd->view_angles + ( local->get_aim_punch() * 2.f ) );
                    float fov = fixes::distance_point_to_line( hitbox_pos , local->get_eye_pos() , view_direction );

                    if ( max_possible_fov > fov )
                    {
                        max_possible_fov = fov;
                        target_index = i;
                    }

                    float best_tagert_time;
                    if ( target_index != -1 && is_visible( local , player ) )
                    {
                        float temp_max_fov = FLT_MAX;
                        vector view_direction = fixes::angle_to_vector( cmd->view_angles + ( local->get_aim_punch() * 2.f ) );

                        for ( int t = 0; t < 24; ++t )
                        {
                            float temp_fov =
                                fixes::distance_point_to_line( hitbox_position[ target_index ][ t ].hitbox_pos ,
                                                               local->get_eye_pos() , view_direction );

                            if ( temp_max_fov > temp_fov &&
                                 hitbox_position[ target_index ][ t ].simulation_time > local->get_simulation_time() - 1 )
                            {
                                temp_max_fov = temp_fov;
                                best_tagert_time = hitbox_position[ target_index ][ t ].simulation_time;
                            }
                        }
                    }
                    cmd->tick_count = time_to_tick( best_tagert_time );
                }
            }
        }
    }

    namespace movement
    {
        namespace bunny_hop
        {
            auto init( user_cmd * cmd , csplayer * local )
            {
                if ( cmd->buttons & cmd_buttons_code::IN_JUMP )
                {
                    if ( local->get_flags() == 256 || local->get_flags() == 262 )
                        cmd->buttons &= ~cmd_buttons_code::IN_JUMP;
                    else if ( local->get_flags() == 257 )
                        cmd->buttons |= cmd_buttons_code::IN_JUMP;
                }
            }
        }

        namespace crounch_spam
        {
            auto init( bool & send_packet , user_cmd * cmd , csplayer * local )
            {
                cmd->buttons |= cmd_buttons_code::IN_BULLRUSH;

                if ( cmd->buttons & cmd_buttons_code::IN_BULLRUSH )
                {
                    if ( local->get_flags() == 263 )
                    {
                        cmd->buttons |= cmd_buttons_code::IN_DUCK;
                        cmd->buttons &= ~cmd_buttons_code::IN_DUCK;
                    }
                }
            }
        }

        namespace auto_strafe
        {
            auto init( user_cmd * cmd , csplayer * local )
            {
                if ( !( local->get_flags() == 257 ) && GetAsyncKeyState( VK_SPACE ) )
                {
                    cmd->foward = ( 10000.f / local->get_velocity().lenght_2d() > 450.f ) ? 450.f : 10000.f
                        / local->get_velocity().lenght_2d();

                    cmd->side = ( cmd->mouse_x != 0 ) ? ( cmd->mouse_x < 0.0f ) ? -450.f : 450.f :
                        ( cmd->command_number % 2 ) == 0 ? -450.f : 450.f;
                }
            }
        }

        namespace auto_stop
        {
            auto init( user_cmd * cmd , csplayer * local , const weapon_struct * weapon_info , csplayer * weapon )
            {
                float max_speed = weapon->has_scope() ? weapon_info->max_speed_alt : weapon_info->max_speed;

                if ( globals::functions::move::velocity.lenght_2d() > max_speed * 0.5f )
                {
                    vector   velocity = globals::functions::move::velocity.lenght_2d();

					vector a = local->get_velocity( ).lenght_2d( );
                    float_t speed = local->get_velocity().lenght();

                    vector direction;
                    fixes::vector_to_angles( velocity , direction );

                    direction.y = cmd->view_angles.y - direction.y;

                    vector forward;
                    fixes::angle_to_vector( direction , forward );
                    vector negated_direction = forward * -speed;

                    float factor = std::fmaxf( negated_direction.x , negated_direction.y ) / 450.f;
                    negated_direction *= factor;

                    cmd->foward = negated_direction.x;
                    cmd->side = negated_direction.y;
                }
            }
        }

        namespace auto_shoot
        {
            auto can_we_shoot( csplayer * local , const weapon_struct * weapon_info , csplayer * weapon )
            {
                if ( weapon->get_next_fire_time() <= local->get_tick_base() * flower_sdk::p_globals_var_base->interval_per_tick &&
                     weapon->get_current_ammo_m1() != 0 )
                    return true;

                return false;
            }

            auto we_are_shooting( user_cmd * cmd )
            {
                if ( cmd->buttons & cmd_buttons_code::IN_ATTACK )
                    return true;
                return false;
            }

            auto init( user_cmd * cmd , csplayer * local , const weapon_struct * weapon_info , csplayer * weapon )
            {
                if ( can_we_shoot( local , weapon_info , weapon ) == true )
                {
                    auto_stop::init( cmd , local , weapon_info , weapon );

                    if ( weapon->has_scope() == true && local->is_scoped() == false )
                        cmd->buttons |= cmd_buttons_code::IN_ATTACK2;

                    if ( weapon_info->type == weapon_type::WEAPONTYPE_SNIPER_RIFLE)
                        cmd->buttons |= cmd_buttons_code::IN_ATTACK;
                    else if( !(weapon_info->type == weapon_type::WEAPONTYPE_SNIPER_RIFLE) && local->get_aim_punch().lenght_2d() <= 0.4 )
                        cmd->buttons |= cmd_buttons_code::IN_ATTACK;
                }
            }
        }
    }

    namespace aimbot
    {
        auto init( bool & send_packet , user_cmd * cmd , csplayer * local , const weapon_struct * weapon_info , csplayer * weapon )
        {
            if ( globals::functions::move::aim_types == 1  )
            {
                for ( int i = 1; i < flower_sdk::p_entity_list->get_highest_entity_index(); i++ )
                {
					if ( weapon_info->type == weapon_type::WEAPONTYPE_C4 ||
						 weapon_info->type == weapon_type::WEAPONTYPE_KNIFE ||
						 cmd->buttons & cmd_buttons_code::IN_ATTACK ||
						 weapon->is_grenade( ) == true ||
						 weapon->is_being_throw( ) == true ||
						 local->get_health( ) == 0 )
						continue;

                    csplayer * player = flower_sdk::p_entity_list->get_entity( i );

                    if ( !player )
                        continue;

                    if ( player->get_team() == local->get_team() )
                        continue;

                    if ( player == local )
                        continue;

                    if ( player->get_dormant() == true )
                        continue;

                    if ( player->get_health() == 0 )
                        continue;

                    if ( player->is_respawning() == true )
                        continue;

                    vector enemy_hitbox = player->get_bone_pos( 6 );

                    vector  local_pos = local->get_eye_pos();

                    vector final_angle = fixes::calc_angle( local_pos , enemy_hitbox );

                    vector local_view;
                    flower_sdk::p_engine->get_view_angles( local_view );

                    float fov = fixes::get_fov( local_view , final_angle );

                    if ( fov > 15 || !backtrack::is_visible( local , player ) )
                        continue;

                    flower_sdk::p_engine->set_view_angles( final_angle );

                    movement::auto_shoot::init( cmd , local , weapon_info , weapon );
                }
            }

            if ( globals::functions::move::aim_types == 2 )
            {
                for ( int i = 1; i < flower_sdk::p_entity_list->get_highest_entity_index(); i++ )
                {
                    csplayer * player = flower_sdk::p_entity_list->get_entity( i );

                    if ( !player )
                        continue;

                    if ( player->get_team() == local->get_team() )
                        continue;

                    if ( player == local )
                        continue;

                    if ( player->get_dormant() == true )
                        continue;

                    if ( player->get_health() == 0 )
                        continue;

                    if ( player->is_respawning() == true )
                        continue;

                    vector enemy_hitbox = player->get_bone_pos( 8 );

                    vector  local_pos = local->get_eye_pos();

                    vector final_angle = fixes::calc_angle( local_pos , enemy_hitbox );

                    vector local_view;
                    flower_sdk::p_engine->get_view_angles( local_view );

                    float fov = fixes::get_fov( local_view , final_angle );

                    if ( fov >= 50 || !backtrack::is_visible( local , player ) )
                        continue;

                    cmd->view_angles = final_angle;

                    movement::auto_shoot::init( cmd , local , weapon_info , weapon );
                }
            }

            if ( globals::functions::move::aim_types == 3 )
            {
                for ( int i = 1; i < flower_sdk::p_entity_list->get_highest_entity_index(); i++ )
                {
                    csplayer * player = flower_sdk::p_entity_list->get_entity( i );

                    if ( !player )
                        continue;

                    if ( player->get_team() == local->get_team() )
                        continue;

                    if ( player == local )
                        continue;

                    if ( player->get_dormant() == true )
                        continue;

                    if ( player->get_health() == 0 )
                        continue;

                    if ( player->is_respawning() == true )
                        continue;

                    vector enemy_hitbox = player->get_bone_pos( 8 );

                    vector  local_pos = local->get_eye_pos();

                    vector final_angle = fixes::calc_angle( local_pos , enemy_hitbox );

                    vector local_view;
                    flower_sdk::p_engine->get_view_angles( local_view );

                    float fov = fixes::get_fov( local_view , final_angle );

                    if ( fov > 360 || !backtrack::is_visible( local , player ) )
                        continue;

                    fixes::clamp_and_normalize( final_angle );

                    cmd->view_angles = final_angle;

                    movement::auto_shoot::init( cmd , local , weapon_info , weapon );
                }
            }
        }
    }

    namespace no_recoil_and_spread
    {
        auto init( user_cmd * cmd , csplayer * local )
        {
			//nope
		}
    }

    namespace fake_lag_value
    {
        auto init( bool & send_packet , user_cmd * cmd , int ammout )
        {
            static int to_chocke = 0;

            if ( !( cmd->buttons & cmd_buttons_code::IN_ATTACK ) )
            {
                if ( to_chocke == ammout )
                {
                    send_packet = true;
                    to_chocke = 0;
                }
                else
                {
                    send_packet = false;
                }
                to_chocke++;
            }
        }
    }

    namespace spammers
    {
        namespace clan_tag
        {
			//omg
            const char* animated_tag_gg[ 10 ] = {
    ">          <",
    ">F         <",
    ">FL        <",
    ">FLO       <",
    ">FLOW      <",
    ">FLOWE     <",
    ">FLOWER     <",
    ">FLOWER  <",
    ">FLOWER  <",
    ">FLOWER <",
            };
            uint32_t clan_tag_counter = 0;

            auto init()
            {
                auto set_clan_tag = [ ] ( const char* tag , const char* name )
                {
                    static auto set_clan_tag_ = reinterpret_cast< void( __fastcall* )( const char* , const char* ) >
                        ( reinterpret_cast< uintptr_t >( GetModuleHandleA( "engine.dll" ) ) + 0x89A10);

                    set_clan_tag_( tag , name );
                };

                static uint32_t time = 0;
                if ( GetTickCount() > time )
                {
                    clan_tag_counter++;

                    if ( clan_tag_counter >= 10 )
                        clan_tag_counter = 0;

                    set_clan_tag( animated_tag_gg[ clan_tag_counter ] , animated_tag_gg[ clan_tag_counter ] );

                    time = GetTickCount() + 500;
                }
            }
        }

        namespace chat_spam
        {
            const char* chat_spam[ 4 ] = {
"say >FLOWER<",
"say >I don't need a condom, i have FLOWER<",
"say >Im not cheating, but if i was, i would be using Flower for CSGO<",
"say >MAD CUZ BAD<",
            };

            uint32_t spammer_counter = 0;
            static uint32_t time = 0;

            auto init()
            {
                if ( GetTickCount() > time )
                {
                    spammer_counter++;

                    if ( spammer_counter >= 4 )
                        spammer_counter = 0;

                    flower_sdk::p_engine->execute_cmd( chat_spam[ spammer_counter ] , 0 );

                    time = GetTickCount() + 100;
                }
            }
        }
    }

    namespace anti_aim
    {
        auto init( bool & send_packet , user_cmd * cmd , csplayer * local , const weapon_struct * weapon_info , csplayer * weapon )
        {
            if ( cmd->buttons & cmd_buttons_code::IN_ATTACK ||
                 local->get_move_type() == move_type::MOVETYPE_LADDER ||
                 weapon->is_grenade() == true ||
                 weapon->is_being_throw() == true ||
                 local->get_health() == 0 )
                return;

            if ( globals::functions::move::anti_aim_x_value == 1 )
            {
                if ( send_packet == false )
                    cmd->view_angles.x = +89;
                else
                    cmd->view_angles.x = +85;
            }

            if ( globals::functions::move::anti_aim_x_value == 2 )
            {
                if ( send_packet == false )
                    cmd->view_angles.x = -89;
                else
                    cmd->view_angles.x = -85;
            }

            if ( globals::functions::move::anti_aim_x_value == 3 )
            {
                if ( send_packet == false )
                {
                    std::default_random_engine random_number( std::random_device {}( ) );
                    std::uniform_real_distribution<float> temp_one( +89.f , -89.f );

                    const float random_angle_one = temp_one( random_number );

                    cmd->view_angles.x = random_angle_one;
                }
                else
                {
                    std::default_random_engine random_number( std::random_device {}( ) );
                    std::uniform_real_distribution<float> temp_one( +89.f , -89.f );

                    const float random_angle_one = temp_one( random_number );

                    cmd->view_angles.x = random_angle_one;
                }
            }

            if ( globals::functions::move::anti_aim_y_value == 1 )
            {
                if ( send_packet == false )
                    cmd->view_angles.y -= 180;
                else
                    cmd->view_angles.y -= 30;
            }

            if ( globals::functions::move::anti_aim_y_value == 2 )
            {
                if ( send_packet == false )
                {
                    std::default_random_engine random_number( std::random_device {}( ) );
                    std::uniform_real_distribution<float> temp_one( +60.f , -60.f );

                    const float random_angle_one = temp_one( random_number );

                    cmd->view_angles.y -= local->get_lower_body_yaw() + random_angle_one;
                }
                else
                {
                    std::default_random_engine random_number( std::random_device {}( ) );
                    std::uniform_real_distribution<float> temp_one( +30.f , -30.f );

                    const float random_angle_one = temp_one( random_number );

                    cmd->view_angles.y -= local->get_lower_body_yaw() + random_angle_one;
                }
            }

            if ( globals::functions::move::anti_aim_y_value == 3 )
            {
                if ( send_packet == false )
                {
					//omg 
                    cmd->view_angles.y += flower_sdk::p_client_state->chokedcommands == 0 ? -59 : 180;
                }
				else
				{
					cmd->view_angles.y += 180.f;
				}


            }
        }
    }
    
    namespace resolver
    {
        auto init( bool & send_packet , user_cmd * cmd , csplayer * local , const weapon_struct * weapon_info , csplayer * weapon )
        {
            for ( int i = 1; i < flower_sdk::p_entity_list->get_highest_entity_index(); i++ )
            {
                csplayer * player = flower_sdk::p_entity_list->get_entity( i );

                if ( !player )
                    continue;

                if ( player->get_team() == local->get_team() )
                    continue;

                if ( player == local )
                    continue;

                if ( player->get_dormant() == true )
                    continue;

                if ( player->get_health() == 0 )
                    continue;

                if ( player->is_respawning() == true )
                    continue;

				//omg lol
                auto shots = local->get_shots_fired();

                switch ( shots % 3 )
                {
                case 1:
                    player->set_eye_angles()->y = 0;
                    break;
                case 2:
                    player->set_eye_angles()->y += 58;
                    break;
                case 3:
                    player->set_eye_angles()->y -= 58;
                    break;
                }
            }
        }
    }

    auto init( bool & send_packet , user_cmd * cmd , csplayer * local , const weapon_struct * weapon_info , csplayer * weapon )
    {
        if ( globals::functions::move::movement == true )
            movement::bunny_hop::init( cmd , local );

        fixes::init_prediction( cmd , local );

        if ( globals::functions::move::aim_types != 0 )
            aimbot::init( send_packet , cmd , local , weapon_info , weapon );

        if( globals::functions::move::resolver == true )
            resolver::init( send_packet , cmd , local , weapon_info , weapon );

        fixes::end_prediction( cmd , local );

        if ( globals::functions::move::auto_strafe == true )
            movement::auto_strafe::init( cmd , local );

        if ( globals::functions::move::crounch_spam == true )
            movement::crounch_spam::init( send_packet , cmd , local );

        if ( globals::functions::move::backtrack_types == 1 )
            backtrack::legit::init( cmd , local );

        if ( globals::functions::move::backtrack_types == 2 )
            backtrack::rage::init( cmd , local );

        if ( globals::functions::move::fake_lag_value != 0 )
            fake_lag_value::init( send_packet , cmd , globals::functions::move::fake_lag_value );

        if ( globals::functions::move::anti_aim_x_value != 0 || globals::functions::move::anti_aim_y_value != 0 )
            anti_aim::init( send_packet , cmd , local , weapon_info , weapon );

        if ( globals::functions::move::no_recoil == true )
            no_recoil_and_spread::init( cmd , local );

        if ( globals::functions::move::change_clan_tag == true )
            spammers::clan_tag::init();

        if ( globals::functions::move::chat_spam == true )
            spammers::chat_spam::init();
    }
}