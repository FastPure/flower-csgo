#pragma once
namespace reset
{
    using prototype_reset = long( __stdcall* )( IDirect3DDevice9* , D3DPRESENT_PARAMETERS*);
    prototype_reset original_reset = nullptr;

    std::unique_ptr<vmt_hook> hook_reset_;

    bool hooked = false;
    long __stdcall hook_reset( IDirect3DDevice9* p_device , D3DPRESENT_PARAMETERS* parameters )
    {
        if ( hooked == false )
        {
            std::cout << "\nreset hooked.";

            hooked = true;
        }

        ImGui_ImplDX9_InvalidateDeviceObjects();

        auto reset = original_reset( p_device , parameters );

        ImGui_ImplDX9_CreateDeviceObjects();

        return reset;
    }
}