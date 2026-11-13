/*
 * tb_thincore.h — Runtime binding to thinCore.dll (hybrid cdecl / stdcall).
 *
 * @author Ji-Feng Tsai (Jiowcl)
 * @email jiowcl@gmail.com
 * @copyright Copyright (c) 2026 Jiowcl. All rights reserved.
 */

#ifndef TB_THINCORE_H
#define TB_THINCORE_H

#include <stddef.h>
#include <windows.h>

#include "thinCore.h"

#define TB_RETURN_STRING_MAX 4096

/**
 * @brief Initialize the thinCore.dll.
 */
int   tb_thincore_init(void);

/**
 * @brief Shutdown the thinCore.dll.
 */
void  tb_thincore_shutdown(void);

/**
 * @brief Add an equate to the ThinBasic namespace.
 * @param szEquate The name of the equate.
 * @param szStringValue The value of the equate.
 * @param dwNumericValue The numeric value of the equate.
 * @param dwConstType The type of the equate.
 * @return 0 if the equate is not added.
 */
DWORD tb_AddEquate(char *szEquate, char *szStringValue, DWORD dwNumericValue, DWORD dwConstType);

/**
 * @brief Load a symbol from a function name.
 * @param szFunctionName The name of the function.
 * @param dwReturnType The return type of the function.
 * @param FunctionCode The function code.
 * @param dwForceOverWrite Whether to force overwrite the function.
 * @return 0 if the symbol is not loaded.
 */
DWORD tb_LoadSymbol(char *szFunctionName, DWORD dwReturnType, void *FunctionCode, DWORD dwForceOverWrite);

/**
 * @brief Load a symbol from a function name.
 * @param szFunctionName The name of the function.
 * @param dwReturnType The return type of the function.
 * @param FunctionCode The function code.
 * @param dwForceOverWrite Whether to force overwrite the function.
 * @return 0 if the symbol is not loaded.
 */
DWORD tb_LoadSymbolFB(char *szFunctionName, DWORD dwReturnType, void *FunctionCode, DWORD dwForceOverWrite);

/**
 * @brief Parse a long.
 * @param result The result of the parse.
 */
void  tb_ParseLong(LONG *result);

/**
 * @brief Parse a string.
 * @param pszString The string to parse.
 */
void  tb_ParseString(char **pszString);

/**
 * @brief Check if the open parenthesis is valid.
 * @param HideError Whether to hide the error.
 * @param AutoPutBack Whether to auto put back the open parenthesis.
 * @return 0 if the open parenthesis is not valid.
 */
DWORD tb_CheckOpenParens(DWORD HideError, DWORD AutoPutBack);

/**
 * @brief Check if the comma is valid.
 * @param HideError Whether to hide the error.
 * @param AutoPutBack Whether to auto put back the comma.
 * @return 0 if the comma is not valid.
 */
DWORD tb_CheckComma(DWORD HideError, DWORD AutoPutBack);

/**
 * @brief Check if the close parenthesis is valid.
 * @param HideError Whether to hide the error.
 * @param AutoPutBack Whether to auto put back the close parenthesis.
 * @return 0 if the close parenthesis is not valid.
 */
DWORD tb_CheckCloseParens(DWORD HideError, DWORD AutoPutBack);

/**
 * @brief Return a string from a null-terminated string.
 * @param sz The string to return.
 * @return The string.
 */
void *tb_return_string(const char *sz);

/**
 * @brief Return a string from a null-terminated string.
 * @param sz The string to return.
 * @param len The length of the string.
 * @return The string.
 */
void *tb_return_string_n(const char *sz, size_t len);

#endif /* TB_THINCORE_H */
