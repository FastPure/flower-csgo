#pragma once
namespace frame_state_notify
{
    using prototype_frame_stage_notify = void( __thiscall* )( void * , int );
    prototype_frame_stage_notify origal_frame_stage_notify = nullptr;

    std::unique_ptr<vmt_hook> hook_frame;

    bool hooked = false;

    void __fastcall hook_frame_stage_notify( void* ecx , void* edx , int stage )
    {
        if ( hooked == false )
        {
            hooked = true;
            std::cout << "\nframe stage hooked";
        }

        csplayer * local = flower_sdk::p_entity_list->get_entity( flower_sdk::p_engine->get_local_player() );

        if ( !local )
            return;

        if ( stage == 5 )
        {
            if ( globals::functions::visuals::others::was_in_third_person == true )
                flower_sdk::p_prediction->set_local_angles( globals::functions::move::last_angle );
        }

        return origal_frame_stage_notify( flower_sdk::p_base_client , stage );
    }
}