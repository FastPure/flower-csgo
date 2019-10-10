#pragma once
namespace prelude
{
    namespace console
    {
        auto init( std::string title )
        {
            AllocConsole();

            FILE *conin , *conout;
            freopen_s( &conin , "conin$" , "r" , stdin );
            freopen_s( &conout , "conout$" , "w" , stderr );
            freopen_s( &conout , "conout$" , "w" , stdout );

            SetConsoleTitle( title.c_str() );

            auto welcome_message=[]()
            {
                std::cout << "\t\t\t\t\t- welcome ! -" <<
                    "\n\t\t\t\t\n\t\t\t\t--  public release  --\n\n";
            };

            welcome_message();
        }
    }

    namespace modules
    {
        HMODULE get_module( std::string module_name )
        {
            auto t = GetModuleHandle( module_name.c_str() );

            if ( t == NULL )
                return get_module( module_name.c_str() );

            return t;
        }
    }

    namespace interfaces
    {
        typedef void* ( *create_interface )( const char * name , int * return_info );

        template <typename T>
        T* get_interface( std::string area_name , std::string module_name , std::string interface_name )
        {
            auto factory = reinterpret_cast< create_interface >( GetProcAddress( modules::get_module( module_name.c_str() ) , "CreateInterface" ) );
            auto result = ( T* ) factory( interface_name.c_str() , nullptr );

            if ( result == nullptr )
            {
                std::cout << "fail to get interface : " << interface_name.c_str() << " at " << area_name.c_str() << "\n";
                std::system( "PAUSE" );
                std::quick_exit( 0 );
            }
            else
            {
                std::transform( interface_name.begin() , interface_name.end() , interface_name.begin() , ::tolower );
                std::cout << area_name.c_str() << " -> found " << interface_name.c_str() << " : " << result << "\n";
            }

            return result;
        };
    }


    auto init()
    {
        auto assing_interfaces = [ ] ()
        {           
            flower_sdk::p_surface = interfaces::get_interface<surface>( "surface" , "vguimatsurface.dll" , "VGUI_Surface031" );
            flower_sdk::p_panel = interfaces::get_interface<panel_id>( "panel" , "vgui2.dll" , "VGUI_Panel009" );

            flower_sdk::p_engine = interfaces::get_interface<engine>( "engine" , "engine.dll" , "VEngineClient014" );
            flower_sdk::p_trace = interfaces::get_interface<trace>( "trace", "engine.dll" , "EngineTraceClient004" );
            flower_sdk::p_model = interfaces::get_interface<model>( "model", "engine.dll" , "VModelInfoClient004" );
            flower_sdk::p_model_render = interfaces::get_interface<model_render>( "model render" , "engine.dll" , "VEngineModel016" );
            flower_sdk::p_material = interfaces::get_interface<material>( "material" , "engine.dll" , "VEngineModel016" );
            flower_sdk::p_material_system = interfaces::get_interface<material_system>( "material system", "materialsystem.dll" , "VMaterialSystem080" );
            flower_sdk::p_cvar = interfaces::get_interface<cvar>("cvar", "vstdlib.dll" , "VEngineCvar007" );
            flower_sdk::p_render_view = interfaces::get_interface<render_view>( "render view" , "engine.dll" , "VEngineRenderView014" );
            flower_sdk::p_debug_overlay = interfaces::get_interface<debug_overlay>( "debug overlay" , "engine.dll" , "VDebugOverlay004" );
            flower_sdk::p_game_event = interfaces::get_interface<game_event_mgr>( "game events", "engine.dll" , "GAMEEVENTSMANAGER002" );
            flower_sdk::p_prediction = interfaces::get_interface<prediction>( "prediction", "client_panorama.dll" , "VClientPrediction001" );
            flower_sdk::p_game_movement = interfaces::get_interface<game_movement>( "game movement" , "client_panorama.dll" , "GameMovement001" );

            flower_sdk::p_base_client = interfaces::get_interface<base_client>( "client" , "client_panorama.dll" , "VClient018" );
            flower_sdk::p_entity_list = interfaces::get_interface<entity_list>( "ent list" , "client_panorama.dll" , "VClientEntityList003" );
                  

            auto get_extra_info = [ ] ()
            {

                flower_sdk::p_move_helper = **( move_helper*** ) ( globals::tools::signature( "client_panorama.dll" , "8B 0D ? ? ? ? 8B 46 08 68" ) + 2 );

                flower_sdk::p_glow = *reinterpret_cast< glow_manager** >( globals::tools::signature
                ( "client_panorama.dll" , "0F 11 05 ? ? ? ? 83 C8 01" ) + 3 );

                flower_sdk::p_client_mode = **( client_mode*** ) ( ( *( DWORD** ) flower_sdk::p_base_client )[ 10 ] + 0x5 );

                flower_sdk::p_client_state = **( client_state*** ) ( globals::tools::signature
                ( "engine.dll" , "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ) + 1 );

                flower_sdk::p_wep_system = *reinterpret_cast< wep_system** >( globals::tools::signature
                ( "client_panorama.dll" , "8B 35 ? ? ? ? FF 10 0F B7 C0" ) + 2 );

                flower_sdk::p_globals_var_base = **( global_var_base*** ) ( ( *( DWORD** ) flower_sdk::p_base_client )[ 0 ] + 0x1B );

                flower_sdk::p_beams = *( render_beams** ) ( globals::tools::signature( 
                    ( "client_panorama.dll" ) , ( "B9 ? ? ? ? A1 ? ? ? ? FF 10 A1 ? ? ? ? B9" ) ) + 1 );

                flower_sdk::p_input = *reinterpret_cast< input** >( globals::tools::signature(
                    "client_panorama.dll" , "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10" ) + 1 );

                globals::game_resources::smoke_cout = *reinterpret_cast< uint32_t ** >
                    ( globals::tools::signature( "client_panorama.dll" , "A3 ? ? ? ? 57 8B CB" ) + 1 );

                globals::functions::move::pred_random_seed = *( int** ) ( globals::tools::signature(
                    "client_panorama.dll" , "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04" ) + 2 );

                if ( flower_sdk::p_client_mode == nullptr || flower_sdk::p_glow == nullptr
                     || globals::game_resources::smoke_cout == nullptr || flower_sdk::p_globals_var_base == nullptr
                     || flower_sdk::p_beams == nullptr || flower_sdk::p_input == nullptr
                     || flower_sdk::p_move_helper == nullptr || globals::functions::move::pred_random_seed == nullptr
                     || flower_sdk::p_wep_system == nullptr || flower_sdk::p_client_state == nullptr )
                {
                    std::cout << "\nfail to assign important module\n";
                    std::system( "PAUSE" );
                    std::quick_exit( 0 );
                }
            };

            get_extra_info();
        
        };

        auto make_vmt_hook = [ ] ()
        {
            static IDirect3DDevice9* shared_api_dx9;
            if ( !shared_api_dx9 )
                shared_api_dx9 = **( IDirect3DDevice9*** ) ( globals::tools::signature( "shaderapidx9.dll" , "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 1 );

            end_scene::hook_end = std::make_unique<vmt_hook>( ( void*** ) shared_api_dx9 );
            end_scene::original_end_scene =
                end_scene::hook_end->hook<end_scene::prototype_end_scene>( 42 , end_scene::hook_end_scene );

            reset::hook_reset_ = std::make_unique<vmt_hook>( ( void*** ) shared_api_dx9 );
            reset::original_reset =
                reset::hook_reset_->hook<reset::prototype_reset>( 16 , reset::hook_reset );


            paint_traverse::hook_paint = std::make_unique<vmt_hook>( ( void*** ) flower_sdk::p_panel );
            paint_traverse::original_paint_traverse =
                paint_traverse::hook_paint->hook<paint_traverse::prototype_paint_traverse>( 41 , paint_traverse::hook_paint_traverse );


            lock_cursor::hook_lock = std::make_unique<vmt_hook>( ( void*** ) flower_sdk::p_surface );
            lock_cursor::original_lock_cursor =
                lock_cursor::hook_lock->hook<lock_cursor::prototype_lock_cursor>( 67 , lock_cursor::hook_lock_cursor );


            override_view::hook_override = std::make_unique<vmt_hook>( ( void*** ) flower_sdk::p_client_mode );
            override_view::original_override_view = 
                override_view::hook_override->hook<override_view::prototype_override_view>( 18 , override_view::hook_override_view );


            post_screen_effects::hook_post = std::make_unique<vmt_hook>( ( void*** ) flower_sdk::p_client_mode );
            post_screen_effects::original_post_screen_effects =
                post_screen_effects::hook_post->hook<post_screen_effects::prototype_post_screen_effects>
                ( 44 , post_screen_effects::hook_post_screen_effects );


            create_move::hook_create = std::make_unique<vmt_hook>( ( void*** ) flower_sdk::p_client_mode );
            create_move::original_create_move = 
                create_move::hook_create->hook<create_move::prototype_create_move>( 24 , create_move::hook_create_move );
            

            frame_state_notify::hook_frame = std::make_unique<vmt_hook>( ( void*** ) flower_sdk::p_base_client );
            frame_state_notify::origal_frame_stage_notify =
                frame_state_notify::hook_frame->hook<frame_state_notify::prototype_frame_stage_notify>
                ( 37 , frame_state_notify::hook_frame_stage_notify );


            paint_traverse::init();
            
            flower_sdk::p_surface->play_sound("ui\\mm_success_lets_roll.wav");
        };

        assing_interfaces();
        configs::init();
        imgui_extras::init_hook();
        make_vmt_hook();
    }
}