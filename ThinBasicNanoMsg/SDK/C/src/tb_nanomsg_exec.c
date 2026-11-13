/*
 * tb_nanomsg_exec.c — ThinBasic keyword executors for the NanoMsg SDK module.
 *
 * @copyright Copyright (c) Ji-Feng Tsai. MIT License.
 */
#define WIN32_LEAN_AND_MEAN
#include "tb_parse.h"
#include "nn_dynload.h"
#include "nn_enums.h"
#include <stdint.h>
#include <string.h>

/**
 * @brief Initialize the NanoMsg library.
 * @return 0 if the library is successfully initialized.
 */
LONG __cdecl Exec_NnLibraryInit(void)
{
    char *path;
    DWORD len;
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_string(&path, &len)) return 0;
    if (!tb_expect_close_parens()) return 0;
    return (LONG)nn_dyn_load_directory(path, len);
}

/**
 * @brief Shutdown the NanoMsg library.
 * @return 0 if the library is successfully shutdown.
 */
LONG __cdecl Exec_NnLibraryShutdown(void)
{
    if (!tb_expect_open_parens() || !tb_expect_close_parens()) return 0;
    nn_dyn_unload();
    return 1;
}

/**
 * @brief Check if the NanoMsg library is loaded.
 * @return 0 if the library is not loaded.
 */
LONG __cdecl Exec_NnLibraryLoaded(void)
{
    if (!tb_expect_open_parens() || !tb_expect_close_parens()) return 0;
    return (LONG)nn_dyn_is_loaded();
}

/**
 * @brief Get the error number from the NanoMsg library.
 * @return The error number.
 */
LONG __cdecl Exec_NnErrno(void)
{
    if (!tb_expect_open_parens() || !tb_expect_close_parens()) return 0;
    return (LONG)nn_api_errno();
}

/**
 * @brief Get the error string from the NanoMsg library.
 * @return The error string.
 */
LONG __cdecl Exec_NnStrerror(void)
{
    LONG err;
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&err)) return 0;
    if (!tb_expect_close_parens()) return 0;
    return (LONG)(intptr_t)nn_api_strerror((int)err);
}

/**
 * @brief Get the error string from the NanoMsg library.
 * @return The error string.
 */
void * __stdcall Exec_NnStrerrorString(void)
{
    LONG err;
    if (!tb_expect_open_parens()) return tb_return_string("");
    if (!tb_parse_int(&err)) return tb_return_string("");
    if (!tb_expect_close_parens()) return tb_return_string("");
    return tb_return_string(nn_api_strerror((int)err));
}

/**
 * @brief Terminate the NanoMsg library.
 * @return 0 if the library is successfully terminated.
 */
LONG __cdecl Exec_NnTerm(void)
{
    if (!tb_expect_open_parens() || !tb_expect_close_parens()) return 0;
    nn_api_term();
    return 1;
}

/**
 * @brief Create a new NanoMsg socket.
 * @return The socket handle.
 */
LONG __cdecl Exec_NnSocket(void)
{
    LONG domain, protocol;
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&domain)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_int(&protocol)) return 0;
    if (!tb_expect_close_parens()) return 0;
    return (LONG)nn_api_socket((int)domain, (int)protocol);
}

/**
 * @brief Close a NanoMsg socket.
 * @return 0 if the socket is successfully closed.
 */
LONG __cdecl Exec_NnClose(void)
{
    LONG socket;
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&socket)) return 0;
    if (!tb_expect_close_parens()) return 0;
    return (LONG)nn_api_close((int)socket);
}

/**
 * @brief Bind a NanoMsg socket to an endpoint.
 * @return 0 if the socket is successfully bound.
 */
LONG __cdecl Exec_NnBind(void)
{
    LONG socket;
    char *endpoint;
    DWORD len;
    char copy[MAX_PATH];
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&socket)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_string(&endpoint, &len)) return 0;
    if (!tb_expect_close_parens()) return 0;
    if (len >= sizeof(copy)) return -1;
    memcpy(copy, endpoint, len);
    copy[len] = '\0';
    return (LONG)nn_api_bind((int)socket, copy);
}

/**
 * @brief Connect a NanoMsg socket to an endpoint.
 * @return 0 if the socket is successfully connected.
 */
LONG __cdecl Exec_NnConnect(void)
{
    LONG socket;
    char *endpoint;
    DWORD len;
    char copy[MAX_PATH];
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&socket)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_string(&endpoint, &len)) return 0;
    if (!tb_expect_close_parens()) return 0;
    if (len >= sizeof(copy)) return -1;
    memcpy(copy, endpoint, len);
    copy[len] = '\0';
    return (LONG)nn_api_connect((int)socket, copy);
}

/**
 * @brief Send a message through a NanoMsg socket.
 * @return 0 if the message is successfully sent.
 */
LONG __cdecl Exec_NnSendStr(void)
{
    LONG socket, flags;
    char *msg;
    DWORD len;
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&socket)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_string(&msg, &len)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_int(&flags)) return 0;
    if (!tb_expect_close_parens()) return 0;
    return (LONG)nn_api_send((int)socket, msg, len, (int)flags);
}

/**
 * @brief Receive a message from a NanoMsg socket.
 * @return The message.
 */
void * __stdcall Exec_NnRecvStr(void)
{
    LONG socket, flags, buflen;
    char static_buf[4096];
    int n;
    if (!tb_expect_open_parens()) return tb_return_string("");
    if (!tb_parse_int(&socket)) return tb_return_string("");
    if (!tb_expect_comma()) return tb_return_string("");
    if (!tb_parse_int(&buflen)) return tb_return_string("");
    if (!tb_expect_comma()) return tb_return_string("");
    if (!tb_parse_int(&flags)) return tb_return_string("");
    if (!tb_expect_close_parens()) return tb_return_string("");
    if (buflen <= 0 || buflen > (LONG)sizeof(static_buf)) buflen = (LONG)sizeof(static_buf);
    n = nn_api_recv((int)socket, static_buf, (size_t)buflen, (int)flags);
    if (n < 0) return tb_return_string("");
    static_buf[n] = '\0';
    return tb_return_string(static_buf);
}

/**
 * @brief Set a socket option for a NanoMsg socket.
 * @return 0 if the socket option is successfully set.
 */
LONG __cdecl Exec_NnSetsockoptStr(void)
{
    LONG socket, level, option, flags;
    char *opt;
    DWORD len;
    (void)flags;
    if (!tb_expect_open_parens()) return 0;
    if (!tb_parse_int(&socket)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_int(&level)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_int(&option)) return 0;
    if (!tb_expect_comma()) return 0;
    if (!tb_parse_string(&opt, &len)) return 0;
    if (!tb_expect_close_parens()) return 0;
    return (LONG)nn_api_setsockopt((int)socket, (int)level, (int)option, opt, len);
}
