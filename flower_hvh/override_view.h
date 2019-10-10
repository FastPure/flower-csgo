#pragma once
namespace override_view
{
    using prototype_override_view = void( __thiscall* )( void * , view_setup* );
    prototype_override_view original_override_view = nullptr;

    std::unique_ptr<vmt_hook> hook_override;

    bool hooked = false;

    void __fastcall hook_override_view( void* ecx , void* edx , view_setup* setup )
    {
        if ( hooked == false )
        {
            hooked = true;
            std::cout << "\noverride view hooked";
        }

        if ( flower_sdk::p_engine->is_connected() == false )
            return;

        csplayer * local = flower_sdk::p_entity_list->get_entity( flower_sdk::p_engine->get_local_player() );

        if ( !local )
            return;

        if ( globals::functions::visuals::others::others_enable == true )
        {
            if ( globals::functions::visuals::others::change_fov != 0 );
            {
                if ( local->is_scoped() == false )
                {
                    setup->fov += globals::functions::visuals::others::change_fov;
                }
            }
        }

        if ( globals::functions::move::no_recoil == true )
        {
            setup->angles -= ( local->get_aim_punch() * 2 * 0.25 );
        }
        original_override_view( flower_sdk::p_client_mode , setup );
    }
}