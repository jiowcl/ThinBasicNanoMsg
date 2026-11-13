/*
 * thinBasic_NanoMsg.c — ThinBasic SDK module entry point.
 *
 * Builds: thinBasic_NanoMsg.dll
 * Usage:  USES "NanoMsg"
 *
 * @copyright Copyright (c) Ji-Feng Tsai. MIT License.
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "thinCore.h"
#include "tb_thincore.h"
#include "nn_dynload.h"
#include "nn_enums.h"

LONG __cdecl Exec_NnLibraryInit(void);
LONG __cdecl Exec_NnLibraryShutdown(void);
LONG __cdecl Exec_NnLibraryLoaded(void);
LONG __cdecl Exec_NnErrno(void);
LONG __cdecl Exec_NnStrerror(void);
void * __stdcall Exec_NnStrerrorString(void);
LONG __cdecl Exec_NnTerm(void);
LONG __cdecl Exec_NnSocket(void);
LONG __cdecl Exec_NnClose(void);
LONG __cdecl Exec_NnBind(void);
LONG __cdecl Exec_NnConnect(void);
LONG __cdecl Exec_NnSendStr(void);
void * __stdcall Exec_NnRecvStr(void);
LONG __cdecl Exec_NnSetsockoptStr(void);

/**
 * @brief Register a function in the ThinBasic namespace.
 * @param name The name of the function.
 * @param ret The return type of the function.
 * @param fn The function pointer.
 */
static void tb_nn_reg(const char *name, DWORD ret, LONG (__cdecl *fn)(void))
{
    tb_LoadSymbol((char *)name, ret, (void *)fn, thinBasic_ForceOverWrite);
}

/**
 * @brief Register an equate in the ThinBasic namespace.
 * @param name The name of the equate.
 * @param value The value of the equate.
 */
static void tb_nn_equate(const char *name, DWORD value)
{
    tb_AddEquate((char *)name, "", value, thinBasic_ConstTypeNumeric);
}

/**
 * @brief Register all NanoMsg functions in the ThinBasic namespace.
 */
static void tb_nn_register_symbols(void)
{
    tb_nn_reg("NnLibraryInit", thinBasic_ReturnCodeLong, &Exec_NnLibraryInit);
    tb_nn_reg("NnLibraryShutdown", thinBasic_ReturnCodeLong, &Exec_NnLibraryShutdown);
    tb_nn_reg("NnLibraryLoaded", thinBasic_ReturnCodeLong, &Exec_NnLibraryLoaded);
    tb_nn_reg("NnErrno", thinBasic_ReturnCodeLong, &Exec_NnErrno);
    tb_nn_reg("NnStrerror", thinBasic_ReturnCodeLong, &Exec_NnStrerror);
    tb_LoadSymbolFB("NnStrerrorString", thinBasic_ReturnString, (void *)&Exec_NnStrerrorString, thinBasic_ForceOverWrite);
    tb_nn_reg("NnTerm", thinBasic_ReturnCodeLong, &Exec_NnTerm);
    tb_nn_reg("NnSocket", thinBasic_ReturnCodeLong, &Exec_NnSocket);
    tb_nn_reg("NnClose", thinBasic_ReturnCodeLong, &Exec_NnClose);
    tb_nn_reg("NnBind", thinBasic_ReturnCodeLong, &Exec_NnBind);
    tb_nn_reg("NnConnect", thinBasic_ReturnCodeLong, &Exec_NnConnect);
    tb_nn_reg("NnSendStr", thinBasic_ReturnCodeLong, &Exec_NnSendStr);
    tb_LoadSymbolFB("NnRecvStr", thinBasic_ReturnString, (void *)&Exec_NnRecvStr, thinBasic_ForceOverWrite);
    tb_nn_reg("NnSetsockoptStr", thinBasic_ReturnCodeLong, &Exec_NnSetsockoptStr);
}

/**
 * @brief Register all NanoMsg equates in the ThinBasic namespace.
 */
static void tb_nn_register_equates(void)
{
    tb_nn_equate("%AF_SP", AF_SP);
    tb_nn_equate("%NN_PAIR", NN_PAIR);
    tb_nn_equate("%NN_PUB", NN_PUB);
    tb_nn_equate("%NN_SUB", NN_SUB);
    tb_nn_equate("%NN_REQ", NN_REQ);
    tb_nn_equate("%NN_REP", NN_REP);
    tb_nn_equate("%NN_PUSH", NN_PUSH);
    tb_nn_equate("%NN_PULL", NN_PULL);
    tb_nn_equate("%NN_BUS", NN_BUS);
    tb_nn_equate("%NN_POLLIN", NN_POLLIN);
    tb_nn_equate("%NN_SOL_SOCKET", NN_SOL_SOCKET);
    tb_nn_equate("%NN_SUB_SUBSCRIBE", NN_SUB_SUBSCRIBE);
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
    nn_dyn_unload();
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
    tb_nn_register_symbols();
    tb_nn_register_equates();
    return 0;
}
