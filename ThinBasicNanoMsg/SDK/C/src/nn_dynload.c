/*
 * nn_dynload.c — Dynamic binding to nanomsg.dll for the ThinBasic SDK module.
 *
 * @copyright Copyright (c) Ji-Feng Tsai. MIT License.
 */
#define WIN32_LEAN_AND_MEAN
#include "nn_dynload.h"

#include <stdio.h>
#include <string.h>

typedef int (__cdecl *nn_socket_fn)(int domain, int protocol);
typedef int (__cdecl *nn_close_fn)(int socket);
typedef int (__cdecl *nn_bind_fn)(int socket, const char *addr);
typedef int (__cdecl *nn_connect_fn)(int socket, const char *addr);
typedef int (__cdecl *nn_send_fn)(int socket, const void *buf, size_t len, int flags);
typedef int (__cdecl *nn_recv_fn)(int socket, void *buf, size_t len, int flags);
typedef int (__cdecl *nn_errno_fn)(void);
typedef const char *(__cdecl *nn_strerror_fn)(int errnum);
typedef int (__cdecl *nn_setsockopt_fn)(int socket, int level, int option, const void *optval, size_t optvallen);
typedef void (__cdecl *nn_term_fn)(void);

/**
 * @brief The NanoMsg API table.
 */
typedef struct nn_api_table {
    HMODULE module;
    int loaded;
    nn_socket_fn socket;
    nn_close_fn close;
    nn_bind_fn bind;
    nn_connect_fn connect;
    nn_send_fn send;
    nn_recv_fn recv;
    nn_errno_fn errno_fn;
    nn_strerror_fn strerror_fn;
    nn_setsockopt_fn setsockopt;
    nn_term_fn term;
} nn_api_table;

static nn_api_table g_nn;

/**
 * @brief Resolve a function in the NanoMsg library.
 * @param name The name of the function.
 * @return The function pointer.
 */
static void *nn_resolve(const char *name)
{
    FARPROC fn = GetProcAddress(g_nn.module, name);
    return fn ? (void *)(INT_PTR)fn : NULL;
}

/**
 * @brief Bind the NanoMsg symbols.
 * @return 0 if the symbols are successfully bound.
 */
static int nn_bind_symbols(void)
{
    g_nn.socket = (nn_socket_fn)nn_resolve("nn_socket");
    g_nn.close = (nn_close_fn)nn_resolve("nn_close");
    g_nn.bind = (nn_bind_fn)nn_resolve("nn_bind");
    g_nn.connect = (nn_connect_fn)nn_resolve("nn_connect");
    g_nn.send = (nn_send_fn)nn_resolve("nn_send");
    g_nn.recv = (nn_recv_fn)nn_resolve("nn_recv");
    g_nn.errno_fn = (nn_errno_fn)nn_resolve("nn_errno");
    g_nn.strerror_fn = (nn_strerror_fn)nn_resolve("nn_strerror");
    g_nn.setsockopt = (nn_setsockopt_fn)nn_resolve("nn_setsockopt");
    g_nn.term = (nn_term_fn)nn_resolve("nn_term");
    return g_nn.socket && g_nn.close && g_nn.bind && g_nn.connect &&
           g_nn.send && g_nn.recv && g_nn.errno_fn && g_nn.strerror_fn && g_nn.setsockopt;
}

/**
 * @brief Trim trailing slashes from a path.
 * @param path The path to trim.
 * @param max_len The maximum length of the path.
 */
static void nn_trim_trailing_slashes(char *path, size_t max_len)
{
    size_t len = 0;
    while (len < max_len && path[len]) len++;
    while (len > 0 && (path[len - 1] == '\\' || path[len - 1] == '/')) {
        path[--len] = '\0';
    }
}

/**
 * @brief Load the NanoMsg library from a directory.
 * @param dir The directory to load the library from.
 * @param dir_len The length of the directory.
 * @return 0 if the library is not loaded.
 */
int nn_dyn_load_directory(const char *dir, DWORD dir_len)
{
    char folder[MAX_PATH];
    char dll_path[MAX_PATH];

    if (!dir || dir_len == 0 || dir_len >= sizeof(folder)) return 0;
    if (g_nn.loaded) return 1;

    memcpy(folder, dir, dir_len);
    folder[dir_len] = '\0';
    nn_trim_trailing_slashes(folder, sizeof(folder));

    if (_snprintf(dll_path, sizeof(dll_path), "%s\\nanomsg.dll", folder) < 0) return 0;

    SetDllDirectoryA(folder);
    g_nn.module = LoadLibraryA(dll_path);
    if (!g_nn.module) {
        SetDllDirectoryA(NULL);
        return 0;
    }
    if (!nn_bind_symbols()) {
        FreeLibrary(g_nn.module);
        g_nn.module = NULL;
        SetDllDirectoryA(NULL);
        memset(&g_nn, 0, sizeof(g_nn));
        return 0;
    }
    g_nn.loaded = 1;
    return 1;
}

/**
 * @brief Unload the NanoMsg library.
 * @return 0 if the library is not unloaded.
 */
void nn_dyn_unload(void)
{
    if (g_nn.module) FreeLibrary(g_nn.module);
    memset(&g_nn, 0, sizeof(g_nn));
    SetDllDirectoryA(NULL);
}

/**
 * @brief Check if the NanoMsg library is loaded.
 * @return 0 if the library is not loaded.
 */
int nn_dyn_is_loaded(void) { 
    return g_nn.loaded; 
}

/**
 * @brief Create a new NanoMsg socket.
 * @param domain The domain of the socket.
 * @param protocol The protocol of the socket.
 * @return The socket handle.
 */
int nn_api_socket(int domain, int protocol) { 
    return g_nn.loaded ? g_nn.socket(domain, protocol) : -1; 
}

/**
 * @brief Close a NanoMsg socket.
 * @param socket The socket to close.
 * @return 0 if the socket is not closed.
 */
int nn_api_close(int socket) { 
    return g_nn.loaded ? g_nn.close(socket) : -1; 
}

/**
 * @brief Bind a NanoMsg socket to an endpoint.
 * @param socket The socket to bind.
 * @param addr The endpoint to bind to.
 * @return 0 if the socket is not bound.
 */
int nn_api_bind(int socket, const char *addr) { 
    return g_nn.loaded ? g_nn.bind(socket, addr) : -1; 
}

/**
 * @brief Connect a NanoMsg socket to an endpoint.
 * @param socket The socket to connect.
 * @param addr The endpoint to connect to.
 * @return 0 if the socket is not connected.
 */
int nn_api_connect(int socket, const char *addr) { 
    return g_nn.loaded ? g_nn.connect(socket, addr) : -1; 
}

/**
 * @brief Send a message through a NanoMsg socket.
 * @param socket The socket to send through.
 * @param buf The message to send.
 * @param len The length of the message.
 * @param flags The flags to send the message with.
 * @return 0 if the message is not sent.
 */
int nn_api_send(int socket, const void *buf, size_t len, int flags) { 
    return g_nn.loaded ? g_nn.send(socket, buf, len, flags) : -1; 
}

/**
 * @brief Receive a message from a NanoMsg socket.
 * @param socket The socket to receive from.
 * @param buf The buffer to receive the message into.
 * @param len The length of the buffer.
 * @param flags The flags to receive the message with.
 * @return 0 if the message is not received.
 */
int nn_api_recv(int socket, void *buf, size_t len, int flags) { 
    return g_nn.loaded ? g_nn.recv(socket, buf, len, flags) : -1; 
}

/**
 * @brief Get the error number from the NanoMsg library.
 * @return The error number.
 */
int nn_api_errno(void) { 
    return g_nn.loaded ? g_nn.errno_fn() : 0; 
}

/**
 * @brief Get the error string from the NanoMsg library.
 * @param errnum The error number.
 * @return The error string.
 */
const char *nn_api_strerror(int errnum) { 
    return g_nn.loaded ? g_nn.strerror_fn(errnum) : ""; 
}

/**
 * @brief Set a socket option for a NanoMsg socket.
 * @param socket The socket to set the option for.
 * @param level The level of the option.
 * @param option The option to set.
 * @param optval The value of the option.
 * @param optvallen The length of the option value.
 * @return 0 if the option is not set.
 */
int nn_api_setsockopt(int socket, int level, int option, const void *optval, size_t optvallen) {
    return g_nn.loaded ? g_nn.setsockopt(socket, level, option, optval, optvallen) : -1;
}

/**
 * @brief Terminate the NanoMsg library.
 * @return 0 if the library is not terminated.
 */
void nn_api_term(void) { 
    if (g_nn.loaded && g_nn.term) g_nn.term(); 
}
