#pragma once
namespace lock_cursor
{
    using prototype_lock_cursor = void( __thiscall* )( surface * );
    prototype_lock_cursor original_lock_cursor = nullptr;

    std::unique_ptr<vmt_hook> hook_lock;

    bool hooked = false;
    void __stdcall hook_lock_cursor()
    {
        if ( hooked == false )
        {
            std::cout << "\nlock cursor hooked.";

            hooked = true;
        }

        if ( globals::menu::checks::open_menu == true )
        {
            flower_sdk::p_surface->unlock_cursor();
            return;
        }

        return original_lock_cursor( flower_sdk::p_surface );
    }
}