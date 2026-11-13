/*
 * tb_nng_exec.c — ThinBasic keyword executors for the NNG SDK module.
 *
 * @copyright Copyright (c) Ji-Feng Tsai. MIT License.
 */
#define WIN32_LEAN_AND_MEAN
#include "tb_parse.h"
#include "nng_dynload.h"
#include "nng_enums.h"
#include <stdint.h>
#include <string.h>

/**
 * @brief Initialize the NNG library.
 * @return 0 if the library is not initialized.
 */
LONG __cdecl Exec_NngLibraryInit(void)
{
    char *path; DWORD len;
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_string(&path, &len)) return 0;
    if (!tb_expect_close_parens()) return 0;
    return (LONG)nng_dyn_load_directory(path, len);
}

/**
 * @brief Shutdown the NNG library.
 * @return 0 if the library is not shutdown.
 */
LONG __cdecl Exec_NngLibraryShutdown(void)
{
    if (!tb_expect_open_parens() || !tb_expect_close_parens()) return 0;
    nng_dyn_unload();
    return 1;
}

/**
 * @brief Check if the NNG library is loaded.
 * @return 0 if the library is not loaded.
 */
LONG __cdecl Exec_NngLibraryLoaded(void)
{
    if (!tb_expect_open_parens() || !tb_expect_close_parens()) return 0;
    return (LONG)nng_dyn_is_loaded();
}

/**
 * @brief Get the error string from the NNG library.
 * @return The error string.
 */
LONG __cdecl Exec_NngStrerror(void)
{
    LONG err;
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&err)) return 0;
    if (!tb_expect_close_parens()) return 0;
    return (LONG)(intptr_t)nng_api_strerror((int)err);
}

/**
 * @brief Get the error string from the NNG library.
 * @return The error string.
 */
void * __stdcall Exec_NngStrerrorString(void)
{
    LONG err;
    if (!tb_expect_open_parens()) return tb_return_string("");
    if (!tb_parse_int(&err)) return tb_return_string("");
    if (!tb_expect_close_parens()) return tb_return_string("");
    return tb_return_string(nng_api_strerror((int)err));
}

/**
 * @brief Open a REP socket.
 * @return 0 if the socket is not opened.
 */
LONG __cdecl Exec_NngRep0Open(void)
{
    LONG sock = 0;
    unsigned u = 0;
    if (!tb_expect_open_parens() || !tb_expect_close_parens()) return 0;
    if (nng_api_rep0_open(&u) != NNG_OK) return 0;
    sock = (LONG)u;
    return sock;
}

/**
 * @brief Open a REQ socket.
 * @return 0 if the socket is not opened.
 */
LONG __cdecl Exec_NngReq0Open(void)
{
    unsigned u = 0;
    if (!tb_expect_open_parens() || !tb_expect_close_parens()) return 0;
    if (nng_api_req0_open(&u) != NNG_OK) return 0;
    return (LONG)u;
}

/**
 * @brief Listen for a NNG socket.
 * @return 0 if the socket is not listened for.
 */
LONG __cdecl Exec_NngListen(void)
{
    LONG sock, flags;
    char *addr; DWORD len; char copy[MAX_PATH];
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&sock)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_string(&addr, &len)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_int(&flags)) return 0;
    if (!tb_expect_close_parens()) return 0;
    if (len >= sizeof(copy)) return -1;
    memcpy(copy, addr, len); copy[len]='\0';
    return (LONG)nng_api_listen((unsigned)sock, copy, (int)flags);
}

/**
 * @brief Dial a NNG socket.
 * @return 0 if the socket is not dialed.
 */
LONG __cdecl Exec_NngDial(void)
{
    LONG sock, flags;
    char *addr; DWORD len; char copy[MAX_PATH];
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&sock)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_string(&addr, &len)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_int(&flags)) return 0;
    if (!tb_expect_close_parens()) return 0;
    if (len >= sizeof(copy)) return -1;
    memcpy(copy, addr, len); copy[len]='\0';
    return (LONG)nng_api_dial((unsigned)sock, copy, (int)flags);
}

/**
 * @brief Send a message through a NNG socket.
 * @return 0 if the message is not sent.
 */
LONG __cdecl Exec_NngSendStr(void)
{
    LONG sock, flags;
    char *msg; DWORD len;
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&sock)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_string(&msg, &len)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_int(&flags)) return 0;
    if (!tb_expect_close_parens()) return 0;
    return (LONG)nng_api_send((unsigned)sock, msg, len, (int)flags);
}

/**
 * @brief Close a NNG socket.
 * @return 0 if the socket is not closed.
 */
LONG __cdecl Exec_NngClose(void)
{
    LONG sock;
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&sock)) return 0;
    if (!tb_expect_close_parens()) return 0;
    return (LONG)nng_api_close((unsigned)sock);
}
