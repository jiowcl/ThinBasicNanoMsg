#ifndef NN_DYNLOAD_H
#define NN_DYNLOAD_H

#include <windows.h>

/**
 * @brief Load the NanoMsg library from a directory.
 * @param dir The directory to load the library from.
 * @param dir_len The length of the directory.
 * @return 0 if the library is not loaded.
 */
int nn_dyn_load_directory(const char *dir, DWORD dir_len);

/**
 * @brief Unload the NanoMsg library.
 */
void nn_dyn_unload(void);

/**
 * @brief Check if the NanoMsg library is loaded.
 * @return 0 if the library is not loaded.
 */
int  nn_dyn_is_loaded(void);

/**
 * @brief Create a new NanoMsg socket.
 * @param domain The domain of the socket.
 * @param protocol The protocol of the socket.
 * @return The socket handle.
 */
int nn_api_socket(int domain, int protocol);

/**
 * @brief Close a NanoMsg socket.
 * @param socket The socket to close.
 * @return 0 if the socket is not closed.
 */
int nn_api_close(int socket);

/**
 * @brief Bind a NanoMsg socket to an endpoint.
 * @param socket The socket to bind.
 * @param addr The endpoint to bind to.
 * @return 0 if the socket is not bound.
 */
int nn_api_bind(int socket, const char *addr);

/**
 * @brief Connect a NanoMsg socket to an endpoint.
 * @param socket The socket to connect.
 * @param addr The endpoint to connect to.
 * @return 0 if the socket is not connected.
 */
int nn_api_connect(int socket, const char *addr);

/**
 * @brief Send a message through a NanoMsg socket.
 * @param socket The socket to send through.
 * @param buf The message to send.
 * @param len The length of the message.
 * @param flags The flags to send the message with.
 * @return 0 if the message is not sent.
 */
int nn_api_send(int socket, const void *buf, size_t len, int flags);

/**
 * @brief Receive a message from a NanoMsg socket.
 * @param socket The socket to receive from.
 * @param buf The buffer to receive the message into.
 * @param len The length of the buffer.
 * @param flags The flags to receive the message with.
 * @return 0 if the message is not received.
 */
int nn_api_recv(int socket, void *buf, size_t len, int flags);

/**
 * @brief Get the error number from the NanoMsg library.
 * @return The error number.
 */
int nn_api_errno(void);

/**
 * @brief Get the error string from the NanoMsg library.
 * @param errnum The error number.
 * @return The error string.
 */
const char *nn_api_strerror(int errnum);

/**
 * @brief Set a socket option for a NanoMsg socket.
 * @param socket The socket to set the option for.
 * @param level The level of the option.
 * @param option The option to set.
 * @param optval The value of the option.
 * @param optvallen The length of the option value.
 * @return 0 if the option is not set.
 */
int nn_api_setsockopt(int socket, int level, int option, const void *optval, size_t optvallen);

/**
 * @brief Terminate the NanoMsg library.
 */
void nn_api_term(void);

#endif
