#pragma once
namespace globals
{
    namespace tools
    {
        template <size_t index , typename ret>
        ret get_virtualfn( void* ecx )
        {
            void** table = *( void*** ) ecx;
            return ( ret ) table[ index ];
        }

#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

        DWORD signature( std::string moduleName , std::string pattern )
        {
            const char* pat = pattern.c_str();
            DWORD firstMatch = 0;
            DWORD rangeStart = ( DWORD ) GetModuleHandleA( moduleName.c_str() );
            MODULEINFO miModInfo; GetModuleInformation( GetCurrentProcess() , ( HMODULE ) rangeStart , &miModInfo , sizeof( MODULEINFO ) );
            DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
            for ( DWORD pCur = rangeStart; pCur < rangeEnd; pCur++ )
            {
                if ( !*pat )
                    return firstMatch;

                if ( *( PBYTE ) pat == '\?' || *( BYTE* ) pCur == getByte( pat ) )
                {
                    if ( !firstMatch )
                        firstMatch = pCur;

                    if ( !pat[ 2 ] )
                        return firstMatch;

                    if ( *( PWORD ) pat == '\?\?' || *( PBYTE ) pat != '\?' )
                        pat += 3;

                    else
                        pat += 2;
                }
                else
                {
                    pat = pattern.c_str();
                    firstMatch = 0;
                }
            }
            return NULL;
        }
    }

    namespace menu
    {
        namespace fonts
        {
            unsigned long  esp;
        }

        namespace checks
        {
            bool open_menu = false , open_visuals = false ,  open_miscs = false , open_rage = false ,
                open_config = false;

            HMODULE dll_handle = NULL;
        }

        namespace game_name
        {
            std::string window_name = "Counter-Strike: Global Offensive";
        }
    }

    namespace functions
    {
        namespace debug
        {
            int r = 0 , g = 0 , b = 0 , a = 0 ,
                r1 = 0 , g1 = 0 , b1 = 0 , a1 = 0 ,

                test1 = 0 , test2 = 0;
                
               float test3 = 0 , test4 = 0 ,
                test5 = 0 , test6 = 0 , test7 = 0 , test8 = 0 , test9 = 0 ,
                test10 = 0;

        }

        namespace move
        {
            bool aim_enable = false , aim_fix_prediction = false ,
                aim_legit_backtrack = false , aim_rage_backtrack = false ,
                no_recoil = false , movement = false , send_packet = false ,
                crounch_spam = false , auto_strafe = false,
                change_clan_tag = false , chat_spam = false,
                auto_shoot = false , we_are_shooting = false,
                resolver = false;

            int backtrack_types = 0 , aim_types = 0,  fake_lag_value = 0,
                anti_aim_x_value = 0, anti_aim_y_value = 0;

            int * pred_random_seed = 0;
            
            float pred_curtime = 0.f , pred_frame_time = 0.f;

            vector last_angle;
            vector velocity;
        }

        namespace esp
        {
            bool esp_enable = false ,
                esp_team = false ,
                esp_box = false ,
                esp_skeleton = false ,
                esp_armor = false ,
                esp_health = false , 
                esp_line = false,
                esp_current_wep_name = false , 
                esp_name = false;
        }

        namespace visuals
        {
            namespace glow
            {
                bool glow_enable = false , glow_team = false;

                static bool glow_entities_to_glow[ 4 ];
            }

            namespace chams
            {
                bool chams_enable = false, chams_team = false,
                    chams_server = false;

                int chams_types = 0;
            }
			
            namespace others
            {
                bool others_enable = false , no_scope = false , night_mode = false ,
                    no_flash = false , no_smoke = false , show_impact = false ,
                    bullet_tracer = false , bullet_tracer_random = false ,
                    was_in_third_person = false , 
                    third_person = false , listen_hitmarkers = false ,
                    should_update_skye = false,
                    should_update_event_bullet_tracer = false,
                    should_update_event_hitmarker = false;

                int change_fov = 0;
            }
        }

        namespace miscs
        {
            bool miscs_main = false, bhop = false;
        }

        namespace configs
        {
            bool save_config = false , update_config = false;
        }
    }

    namespace game_resources
    {
        uint32_t
            health = 0x100 , team = 0xF4 , dormant = 0xED , flags = 0x104 , armor = 0xB328 ,
            respawning = 0x3928 , active_weapon = 0x2EF8 , origin = 0x138 , view_offset = 0x108 ,
            owner_entity = 0x14C , flash_duration = 0xA3E0 , scoped = 0x390A , shots_fired = 0xA370 ,
            aim_punch = 0x302C , tick_base = 0x342C , velocity = 0x114 , eye_angle = 0xB32C ,
            simulation_time = 0x268 , net_chan = 0x9C , current_ammo_m1 = 0x3244, move_type = 0x25C,
            item_def_index = 0x2FAA , next_fire = 0x3218 , trow_time = 0x3394, pin_pulled = 0x3392,
            current_ammo_m2 = 0x3248 , lower_body_yaw = 0x3A78, anim_state = 0x3900;

        uint32_t * smoke_cout = 0;
    }
}