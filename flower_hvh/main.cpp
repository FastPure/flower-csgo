#include "headers.h"

void entry_point()
{
    prelude::console::init( "flower" );
    prelude::init();
}

BOOL WINAPI DllMain( HMODULE instance , DWORD reason , LPVOID reserved )
{
    switch ( reason )
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls( instance );
        globals::menu::checks::dll_handle = instance;
        CreateThread( NULL , NULL , ( LPTHREAD_START_ROUTINE ) entry_point , NULL , NULL , NULL );
        break;
    case DLL_PROCESS_DETACH:
        MessageBox( NULL , "detached" , "flower" , MB_OK );
        FreeLibraryAndExitThread( globals::menu::checks::dll_handle , 0 );
        break;
    }
    return TRUE;
}