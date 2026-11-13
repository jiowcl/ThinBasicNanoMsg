/*
 * nng_dynload.c — Dynamic binding to nng.dll for the ThinBasic SDK module.
 *
 * @copyright Copyright (c) Ji-Feng Tsai. MIT License.
 */
#define WIN32_LEAN_AND_MEAN
#include "nng_dynload.h"
#include <string.h>
#include <stdio.h>

typedef int (__cdecl *nng_init_fn)(const void *params);
typedef void (__cdecl *nng_fini_fn)(void);
typedef int (__cdecl *nng_rep0_open_fn)(unsigned *sock);
typedef int (__cdecl *nng_req0_open_fn)(unsigned *sock);
typedef int (__cdecl *nng_pub0_open_fn)(unsigned *sock);
typedef int (__cdecl *nng_sub0_open_fn)(unsigned *sock);
typedef int (__cdecl *nng_listen_fn)(unsigned sock, const char *addr, void *listener, int flags);
typedef int (__cdecl *nng_dial_fn)(unsigned sock, const char *addr, void *dialer, int flags);
typedef int (__cdecl *nng_send_fn)(unsigned sock, const void *buf, size_t len, int flags);
typedef int (__cdecl *nng_recv_fn)(unsigned sock, void *buf, size_t *len, int flags);
typedef int (__cdecl *nng_close_fn)(unsigned sock);
typedef int (__cdecl *nng_sub_subscribe_fn)(unsigned sock, const void *topic, size_t len);
typedef const char *(__cdecl *nng_strerror_fn)(int err);

/**
 * @brief The NNG API table.
 */
typedef struct nng_api_table {
    HMODULE module;
    int loaded;
    nng_init_fn init;
    nng_fini_fn fini;
    nng_rep0_open_fn rep0_open;
    nng_req0_open_fn req0_open;
    nng_pub0_open_fn pub0_open;
    nng_sub0_open_fn sub0_open;
    nng_listen_fn listen;
    nng_dial_fn dial;
    nng_send_fn send;
    nng_recv_fn recv;
    nng_close_fn close;
    nng_sub_subscribe_fn subscribe;
    nng_strerror_fn strerror_fn;
} nng_api_table;

static nng_api_table g_nng;

/**
 * @brief Resolve a symbol in the NNG library.
 * @param name The name of the symbol.
 * @return The symbol.
 */
static void *nng_resolve(const char *name)
{
    FARPROC fn = GetProcAddress(g_nng.module, name);
    return fn ? (void *)(INT_PTR)fn : NULL;
}

/**
 * @brief Bind the NNG symbols.
 * @return 0 if the symbols are not bound.
 */
static int nng_bind_symbols(void)
{
    g_nng.init = (nng_init_fn)nng_resolve("nng_init");
    g_nng.fini = (nng_fini_fn)nng_resolve("nng_fini");
    g_nng.rep0_open = (nng_rep0_open_fn)nng_resolve("nng_rep0_open");
    g_nng.req0_open = (nng_req0_open_fn)nng_resolve("nng_req0_open");
    g_nng.pub0_open = (nng_pub0_open_fn)nng_resolve("nng_pub0_open");
    g_nng.sub0_open = (nng_sub0_open_fn)nng_resolve("nng_sub0_open");
    g_nng.listen = (nng_listen_fn)nng_resolve("nng_listen");
    g_nng.dial = (nng_dial_fn)nng_resolve("nng_dial");
    g_nng.send = (nng_send_fn)nng_resolve("nng_send");
    g_nng.recv = (nng_recv_fn)nng_resolve("nng_recv");
    g_nng.close = (nng_close_fn)nng_resolve("nng_socket_close");
    g_nng.subscribe = (nng_sub_subscribe_fn)nng_resolve("nng_sub0_socket_subscribe");
    g_nng.strerror_fn = (nng_strerror_fn)nng_resolve("nng_strerror");
    return g_nng.init && g_nng.fini && g_nng.rep0_open && g_nng.req0_open && g_nng.listen &&
           g_nng.dial && g_nng.send && g_nng.recv && g_nng.close && g_nng.strerror_fn;
}

/**
 * @brief Load the NNG library from a directory.
 * @param dir The directory to load the library from.
 * @param dir_len The length of the directory.
 * @return 0 if the library is not loaded.
 */
int nng_dyn_load_directory(const char *dir, DWORD dir_len)
{
    char folder[MAX_PATH];
    char dll_path[MAX_PATH];
    if (!dir || dir_len == 0 || dir_len >= sizeof(folder)) return 0;
    if (g_nng.loaded) return 1;
    memcpy(folder, dir, dir_len);
    folder[dir_len] = '\0';
  while (dir_len > 0 && (folder[dir_len-1]=='\\'||folder[dir_len-1]=='/')) folder[--dir_len]='\0';
    _snprintf(dll_path, sizeof(dll_path), "%s\\nng.dll", folder);
    SetDllDirectoryA(folder);
    g_nng.module = LoadLibraryA(dll_path);
    if (!g_nng.module) { SetDllDirectoryA(NULL); return 0; }
    if (!nng_bind_symbols()) {
        FreeLibrary(g_nng.module);
        g_nng.module = NULL;
        SetDllDirectoryA(NULL);
        memset(&g_nng, 0, sizeof(g_nng));
        return 0;
    }
    g_nng.loaded = 1;
    if (g_nng.init(NULL) != 0) {
        nng_dyn_unload();
        return 0;
    }
    return 1;
}

/**
 * @brief Unload the NNG library.
 */
void nng_dyn_unload(void)
{
    if (g_nng.loaded && g_nng.fini) g_nng.fini();
    if (g_nng.module) FreeLibrary(g_nng.module);
    memset(&g_nng, 0, sizeof(g_nng));
    SetDllDirectoryA(NULL);
}

/**
 * @brief Check if the NNG library is loaded.
 * @return 0 if the library is not loaded.
 */
int nng_dyn_is_loaded(void) { return g_nng.loaded; }

/**
 * @brief Initialize the NNG library.
 * @return 0 if the library is not initialized.
 */
int nng_api_init(void) { 
    return g_nng.loaded ? g_nng.init(NULL) : -1; 
}

/**
 * @brief Initialize the NNG library.
 * @return 0 if the library is not initialized.
 */
void nng_api_fini(void) { 
    if (g_nng.loaded && g_nng.fini) g_nng.fini(); 
}

/**
 * @brief Open a REP socket.
 * @param sock The socket to open.
 * @return 0 if the socket is not opened.
 */
int nng_api_rep0_open(unsigned *sock) { 
    return g_nng.loaded ? g_nng.rep0_open(sock) : -1; 
}

/**
 * @brief Open a REQ socket.
 * @param sock The socket to open.
 * @return 0 if the socket is not opened.
 */
int nng_api_req0_open(unsigned *sock) { 
    return g_nng.loaded ? g_nng.req0_open(sock) : -1; 
}

/**
 * @brief Open a PUB socket.
 * @param sock The socket to open.
 * @return 0 if the socket is not opened.
 */
int nng_api_pub0_open(unsigned *sock) { 
    return g_nng.loaded ? g_nng.pub0_open(sock) : -1; 
}

/**
 * @brief Open a SUB socket.
 * @param sock The socket to open.
 * @return 0 if the socket is not opened.
 */
int nng_api_sub0_open(unsigned *sock) { 
    return g_nng.loaded ? g_nng.sub0_open(sock) : -1; 
}

/**
 * @brief Listen for a NNG socket.
 * @param sock The socket to listen for.
 * @param addr The address to listen for.
 * @param flags The flags to listen for the socket with.
 * @return 0 if the socket is not listened for.
 */
int nng_api_listen(unsigned sock, const char *addr, int flags) { 
    return g_nng.loaded ? g_nng.listen(sock, addr, NULL, flags) : -1; 
}

/**
 * @brief Dial a NNG socket.
 * @param sock The socket to dial.
 * @param addr The address to dial.
 * @param flags The flags to dial the socket with.
 * @return 0 if the socket is not dialed.
 */
int nng_api_dial(unsigned sock, const char *addr, int flags) { 
    return g_nng.loaded ? g_nng.dial(sock, addr, NULL, flags) : -1; 
}

/**
 * @brief Send a message through a NNG socket.
 * @param sock The socket to send through.
 * @param buf The message to send.
 * @param len The length of the message.
 * @param flags The flags to send the message with.
 * @return 0 if the message is not sent.
 */
int nng_api_send(unsigned sock, const void *buf, size_t len, int flags) { 
    return g_nng.loaded ? g_nng.send(sock, buf, len, flags) : -1; 
}

/**
 * @brief Receive a message from a NNG socket.
 * @param sock The socket to receive from.
 * @param buf The buffer to receive the message into.
 * @param len The length of the buffer.
 * @param flags The flags to receive the message with.
 * @return 0 if the message is not received.
 */
int nng_api_recv(unsigned sock, void *buf, size_t *len, int flags) { 
    return g_nng.loaded ? g_nng.recv(sock, buf, len, flags) : -1; 
}

/**
 * @brief Close a NNG socket.
 * @param sock The socket to close.
 * @return 0 if the socket is not closed.
 */
int nng_api_close(unsigned sock) { 
    return g_nng.loaded ? g_nng.close(sock) : -1; 
}

/**
 * @brief Subscribe to a NNG socket.
 * @param sock The socket to subscribe to.
 * @param topic The topic to subscribe to.
 * @return 0 if the socket is not subscribed to.
 */
int nng_api_subscribe(unsigned sock, const char *topic) {
    size_t len;
    if (!g_nng.loaded || !g_nng.subscribe)
        return -1;
    if (!topic)
        return -1;
    len = strlen(topic);
    return g_nng.subscribe(sock, topic, len);
}

/**
 * @brief Get the error string from the NNG library.
 * @param err The error number.
 * @return The error string.
 */
const char *nng_api_strerror(int err) { 
    return g_nng.loaded ? g_nng.strerror_fn(err) : ""; 
}
