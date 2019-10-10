#pragma once
extern LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam );

namespace imgui_extras
{
    typedef LRESULT( CALLBACK* WNDPROC )( HWND , UINT , WPARAM , LPARAM );

    WNDPROC original_win_proc;

    LRESULT __stdcall win_proc( const HWND hwnd , UINT msg , WPARAM param , LPARAM lparam )
    {
        if ( true && ImGui_ImplWin32_WndProcHandler( hwnd , msg , param , lparam ) )
            return true;

        return CallWindowProc( original_win_proc , hwnd , msg , param , lparam );
    }

    auto init_hook()
    {
        HWND  window = FindWindowA( NULL , globals::menu::game_name::window_name.c_str() );
        original_win_proc = ( WNDPROC ) SetWindowLongPtr( window , GWL_WNDPROC , ( LONG_PTR ) win_proc );

        IDirect3D9 * p_d3d = Direct3DCreate9( D3D_SDK_VERSION );

        D3DPRESENT_PARAMETERS d3dpp { 0 };
        d3dpp.hDeviceWindow = window , d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD , d3dpp.Windowed = TRUE;

        IDirect3DDevice9 * p_device  = nullptr;
        if ( FAILED( p_d3d->CreateDevice( 0 , D3DDEVTYPE_HAL , d3dpp.hDeviceWindow , D3DCREATE_SOFTWARE_VERTEXPROCESSING , &d3dpp , &p_device ) ) )
            p_d3d->Release();

        void ** pVTable = *reinterpret_cast< void*** >( p_device );

        if ( p_device )
            p_device->Release() , p_device = nullptr;

        std::cout << "\nimgui status : 1/2";
    }

    auto render_menu()
    {              
        ImGui::Begin( "welcome to flower , a old project of mine" , &globals::menu::checks::open_menu ,
                      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize );
        ImGui::SetWindowSize( ImVec2( 400 , 200 ) , 0 );

        if ( ImGui::BeginMainMenuBar() )
        {
            if ( ImGui::BeginMenu( "movement" , &globals::menu::checks::open_visuals ) )
            {
                ImGui::Checkbox( "enable move" , &globals::functions::move::aim_enable );

                ImGui::Checkbox( "bunny hop" , &globals::functions::move::movement );
                ImGui::Checkbox( "auto stafe" , &globals::functions::move::auto_strafe );
                ImGui::Checkbox( "crounch spam" , &globals::functions::move::crounch_spam );

                static const char * backtrack_type [ ] { "off", "legit", "rage" };
                ImGui::Combo( "backtrack type" , &globals::functions::move::backtrack_types , backtrack_type , IM_ARRAYSIZE( backtrack_type ) );

                static const char * aim_type [ ] { "off", "legit", "rage - dm" , "rage - mm"};
                ImGui::Combo( "aim type" , &globals::functions::move::aim_types , aim_type , IM_ARRAYSIZE( aim_type ) );

                static const char * anti_aim_type_x [ ] { "off", "down", "up", "mix" };
                ImGui::Combo( "anti aim x" , &globals::functions::move::anti_aim_x_value , anti_aim_type_x , IM_ARRAYSIZE( anti_aim_type_x ) );

                static const char * anti_aim_type_y [ ] { "off", "backwards", "break lby" ,"smart aa" };
                ImGui::Combo( "anti aim y" , &globals::functions::move::anti_aim_y_value , anti_aim_type_y , IM_ARRAYSIZE( anti_aim_type_y ) );

                ImGui::Checkbox( "no recoil" , &globals::functions::move::no_recoil );
                ImGui::Checkbox( "beta resolver" , &globals::functions::move::resolver );

                ImGui::Checkbox( "clan tag changer" , &globals::functions::move::change_clan_tag );
                ImGui::Checkbox( "chat spam" , &globals::functions::move::chat_spam );

                ImGui::SliderInt( "fake lag" , &globals::functions::move::fake_lag_value , 0 , 15 );

                ImGui::Separator();

                ImGui::EndMenu();
            }

            if ( ImGui::BeginMenu( "visuals" , &globals::menu::checks::open_visuals ) )
            {
                ImGui::Checkbox( "enable esp" , &globals::functions::esp::esp_enable );

                ImGui::Checkbox( "esp on team" , &globals::functions::esp::esp_team );
                ImGui::Checkbox( "box" , &globals::functions::esp::esp_box );
                ImGui::Checkbox( "name" , &globals::functions::esp::esp_name );
                ImGui::Checkbox( "health" , &globals::functions::esp::esp_health );
                ImGui::Checkbox( "armor" , &globals::functions::esp::esp_armor );
                ImGui::Checkbox( "line" , &globals::functions::esp::esp_line );
                ImGui::Checkbox( "current weapon name" , &globals::functions::esp::esp_current_wep_name );
                ImGui::Checkbox( "skeleton" , &globals::functions::esp::esp_skeleton );




                ImGui::Separator();

                ImGui::Checkbox( "enable glow" , &globals::functions::visuals::glow::glow_enable );
                ImGui::Checkbox( "glow on team" , &globals::functions::visuals::glow::glow_team );


                static const char * glow_entities [ ] { "enemy", "c4", "chiken", "drone"};
                static std::string glow_entities_clear = "";

                if ( ImGui::BeginCombo( "glow entities" , glow_entities_clear.c_str() ) )
                {
                    glow_entities_clear = "";
                    std::vector<std::string> words;

                    for ( uint32_t i = 0; i < IM_ARRAYSIZE( glow_entities ); i++ )
                    {
                        ImGui::Selectable( glow_entities[ i ] , &globals::functions::visuals::glow::glow_entities_to_glow[ i ] , 
                                           ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups );
                        if ( globals::functions::visuals::glow::glow_entities_to_glow[ i ] )
                            words.push_back( glow_entities[ i ] );
                    }
                    for ( uint32_t i = 0; i < words.size(); i++ )
                    {
                        if ( words.size() == 1 )
                            glow_entities_clear += words.at( i );
                        else if ( !( i == words.size() - 1 ) )
                            glow_entities_clear += words.at( i ) + ",";
                        else
                            glow_entities_clear += words.at( i );
                    }
                    ImGui::EndCombo();
                }
                
                ImGui::Separator();
                               

                ImGui::Checkbox( "enable chams" , &globals::functions::visuals::chams::chams_enable );
                ImGui::Checkbox( "chams on team" , &globals::functions::visuals::chams::chams_team );              
                static const char * chams_types [ ] { "solid", "glass" , "glow"};
                ImGui::Combo( "chams types" , &globals::functions::visuals::chams::chams_types , chams_types , IM_ARRAYSIZE( chams_types ) );
                ImGui::Checkbox( "show server chams" , &globals::functions::visuals::chams::chams_server );

                


                ImGui::Separator();

                ImGui::Checkbox( "enable visuals" , &globals::functions::visuals::others::others_enable );

                ImGui::Checkbox( "night mode" , &globals::functions::visuals::others::night_mode );
                ImGui::Checkbox( "no flash" , &globals::functions::visuals::others::no_flash );
                ImGui::Checkbox( "no smoke" , &globals::functions::visuals::others::no_smoke );
                ImGui::Checkbox( "no scope" , &globals::functions::visuals::others::no_scope );
                ImGui::Checkbox( "show impact" , &globals::functions::visuals::others::show_impact );
                ImGui::Checkbox( "bullet tracer" , &globals::functions::visuals::others::bullet_tracer );
                ImGui::Checkbox( "random trace" , &globals::functions::visuals::others::bullet_tracer_random );
                ImGui::Checkbox( "hitmarker" , &globals::functions::visuals::others::listen_hitmarkers );
                ImGui::Checkbox( "thirdperson" , &globals::functions::visuals::others::third_person );

                ImGui::SliderInt( "fov" , &globals::functions::visuals::others::change_fov , 10 , 120 );

                ImGui::Separator();

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        ImGui::Text( "#important" );
        ImGui::Text( "this public release of my old base (dissedia) " );
        ImGui::Text( "thus, it has bugs, crashes & unfinished stuff" );
        ImGui::Text( "#version" );
        ImGui::Text( "your 1337 version here" );
        ImGui::Text( "current config patch : %s" , configs::config_patch_txt );
        ImGui::Text( "#change-log" );
		ImGui::Text( "null");

        ImGui::End();
    }
}

namespace end_scene
{
    using prototype_end_scene = long( __stdcall* )( IDirect3DDevice9* );
    prototype_end_scene original_end_scene = nullptr;

    std::unique_ptr<vmt_hook> hook_end;

    bool hooked = false; 
    long __stdcall hook_end_scene( IDirect3DDevice9* p_device )
    {
        if ( hooked == false )
        {       
            ImGui::CreateContext();

            ImGui_ImplWin32_Init( FindWindowA( NULL , globals::menu::game_name::window_name.c_str() ) );
            ImGui_ImplDX9_Init( p_device );

            std::cout << "\nimgui status : 2/2\nend scene hooked.";
            hooked = true;
        }

        if ( GetAsyncKeyState( VK_INSERT ) & 1 )
            globals::menu::checks::open_menu = !globals::menu::checks::open_menu;
       
        if ( globals::menu::checks::open_menu == true )
        {
            DWORD old_color;
            p_device->GetRenderState( D3DRS_COLORWRITEENABLE , &old_color );
            p_device->SetRenderState( D3DRS_COLORWRITEENABLE , 0xffffffff );

            ImGui_ImplDX9_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

			ImGui::GetIO( ).MouseDrawCursor = globals::menu::checks::open_menu;

            imgui_extras::render_menu();

            ImGui::EndFrame();
            ImGui::Render();

            ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData() );

            p_device->SetRenderState( D3DRS_COLORWRITEENABLE , old_color );
        }
        
        return original_end_scene( p_device );
    }
}
