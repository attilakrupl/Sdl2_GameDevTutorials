#include <windows.h>

void NTAPI tls_callback( PVOID DllHandle, DWORD dwReason, PVOID )
{
    if(( dwReason == DLL_THREAD_ATTACH ) ||
        ( dwReason == DLL_PROCESS_ATTACH ))
    {
        bool debIsPres = ::IsDebuggerPresent();
        if (debIsPres)
        {
            ::exit( -666 );
        }
    }
}

#ifdef _WIN64
#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:tls_callback_func")
#else
#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:_tls_callback_func")
#endif

#ifdef _WIN64
#pragma const_seg(".CRT$XLF")
EXTERN_C const
#else
#pragma data_seg(".CRT$XLF")
EXTERN_C
#endif //_WIN64

PIMAGE_TLS_CALLBACK tls_callback_func = tls_callback;

#ifdef _WIN64
#pragma const_seg()
#else
#pragma data_seg()
#endif //_WIN64