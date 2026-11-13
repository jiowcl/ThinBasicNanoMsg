#ifndef NNG_DYNLOAD_H
#define NNG_DYNLOAD_H

#include <windows.h>

int  nng_dyn_load_directory(const char *dir, DWORD dir_len);
void nng_dyn_unload(void);
int  nng_dyn_is_loaded(void);

int         nng_api_init(void);
void        nng_api_fini(void);
int         nng_api_rep0_open(unsigned *sock);
int         nng_api_req0_open(unsigned *sock);
int         nng_api_pub0_open(unsigned *sock);
int         nng_api_sub0_open(unsigned *sock);
int         nng_api_listen(unsigned sock, const char *addr, int flags);
int         nng_api_dial(unsigned sock, const char *addr, int flags);
int         nng_api_send(unsigned sock, const void *buf, size_t len, int flags);
int         nng_api_recv(unsigned sock, void *buf, size_t *len, int flags);
int         nng_api_close(unsigned sock);
int         nng_api_subscribe(unsigned sock, const char *topic);
const char *nng_api_strerror(int err);

#endif
