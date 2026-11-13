/*
 * thinBasic_NNG.c — ThinBasic SDK module entry point.
 *
 * Builds: thinBasic_NNG.dll
 * Usage:  USES "NNG"
 *
 * @copyright Copyright (c) Ji-Feng Tsai. MIT License.
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "thinCore.h"
#include "tb_thincore.h"
#include "nng_dynload.h"
#include "nng_enums.h"

/**
 * @brief Initialize the NNG library.
 * @return 0 if the library is not initialized.
 */
LONG __cdecl Exec_NngLibraryInit(void);

/**
 * @brief Shutdown the NNG library.
 * @return 0 if the library is not shutdown.
 */
LONG __cdecl Exec_NngLibraryShutdown(void);

/**
 * @brief Check if the NNG library is loaded.
 * @return 0 if the library is not loaded.
 */
LONG __cdecl Exec_NngLibraryLoaded(void);

/**
 * @brief Get the error string from the NNG library.
 * @return The error string.
 */
LONG __cdecl Exec_NngStrerror(void);

/**
 * @brief Get the error string from the NNG library.
 * @return The error string.
 */
void * __stdcall Exec_NngStrerrorString(void);

/**
 * @brief Open a REP socket.
 * @return 0 if the socket is not opened.
 */
LONG __cdecl Exec_NngRep0Open(void);

/**
 * @brief Open a REQ socket.
 * @return 0 if the socket is not opened.
 */
LONG __cdecl Exec_NngReq0Open(void);

/**
 * @brief Open a PUB socket.
 * @return 0 if the socket is not opened.
 */
LONG __cdecl Exec_NngPub0Open(void);

/**
 * @brief Subscribe to a NNG socket.
 * @return 0 if the socket is not subscribed to.
 */
LONG __cdecl Exec_NngSub0Open(void);

/**
 * @brief Listen for a NNG socket.
 * @return 0 if the socket is not listened for.
 */
LONG __cdecl Exec_NngListen(void);

/**
 * @brief Dial a NNG socket.
 * @return 0 if the socket is not dialed.
 */
LONG __cdecl Exec_NngDial(void);

/**
 * @brief Send a message through a NNG socket.
 * @return 0 if the message is not sent.
 */
LONG __cdecl Exec_NngSendStr(void);

/**
 * @brief Close a NNG socket.
 * @return 0 if the socket is not closed.
 */
LONG __cdecl Exec_NngClose(void);

/**
 * @brief Register a symbol in the ThinBasic namespace.
 * @param name The name of the symbol.
 * @param ret The return type of the symbol.
 * @param fn The function pointer.
 */
static void tb_nng_reg(const char *name, DWORD ret, LONG (__cdecl *fn)(void))
{
    tb_LoadSymbol((char *)name, ret, (void *)fn, thinBasic_ForceOverWrite);
}

/**
 * @brief Register an equate in the ThinBasic namespace.
 * @param name The name of the equate.
 * @param value The value of the equate.
 */
static void tb_nng_equate(const char *name, DWORD value)
{
    tb_AddEquate((char *)name, "", value, thinBasic_ConstTypeNumeric);
}

/**
 * @brief Register all symbols in the ThinBasic namespace.
 */
static void tb_nng_register_symbols(void)
{
    tb_nng_reg("NngLibraryInit", thinBasic_ReturnCodeLong, &Exec_NngLibraryInit);
    tb_nng_reg("NngLibraryShutdown", thinBasic_ReturnCodeLong, &Exec_NngLibraryShutdown);
    tb_nng_reg("NngLibraryLoaded", thinBasic_ReturnCodeLong, &Exec_NngLibraryLoaded);
    tb_nng_reg("NngStrerror", thinBasic_ReturnCodeLong, &Exec_NngStrerror);
    tb_LoadSymbolFB("NngStrerrorString", thinBasic_ReturnString, (void *)&Exec_NngStrerrorString, thinBasic_ForceOverWrite);
    tb_nng_reg("NngRep0Open", thinBasic_ReturnCodeLong, &Exec_NngRep0Open);
    tb_nng_reg("NngReq0Open", thinBasic_ReturnCodeLong, &Exec_NngReq0Open);
    tb_nng_reg("NngListen", thinBasic_ReturnCodeLong, &Exec_NngListen);
    tb_nng_reg("NngDial", thinBasic_ReturnCodeLong, &Exec_NngDial);
    tb_nng_reg("NngSendStr", thinBasic_ReturnCodeLong, &Exec_NngSendStr);
    tb_nng_reg("NngClose", thinBasic_ReturnCodeLong, &Exec_NngClose);
}

/**
 * @brief Register all equates in the ThinBasic namespace.
 */
static void tb_nng_register_equates(void)
{
    tb_nng_equate("%NNG_OK", NNG_OK);
    tb_nng_equate("%NNG_FLAG_NONBLOCK", NNG_FLAG_NONBLOCK);
}

/**
 * @brief The main entry point for the DLL.
 * @param instance The instance of the DLL.
 * @param reason The reason for the call.
 * @param reserved Reserved.
 * @return TRUE if the DLL is successfully loaded.
 */
BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    (void)instance; (void)reason; (void)reserved;
    return TRUE;
}

/**
 * @brief Unload the local symbols.
 * @return 0 if the symbols are successfully unloaded.
 */
DWORD __declspec(dllexport) __cdecl _UnLoadLocalSymbols(void)
{
    nng_dyn_unload();
    tb_thincore_shutdown();
    return 0;
}

/**
 * @brief Load the local symbols.
 * @param app_path The path to the application.
 * @return 0 if the symbols are successfully loaded.
 */
DWORD __declspec(dllexport) __cdecl _LoadLocalSymbols(char *app_path)
{
    (void)app_path;
    if (!tb_thincore_init()) return 0;
    tb_nng_register_symbols();
    tb_nng_register_equates();
    return 0;
}
