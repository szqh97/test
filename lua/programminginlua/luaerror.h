#ifndef _LUA_ERROR_H_
#define _LUA_ERROR_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}
#endif



void error(lua_State *L, const char* fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr,fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

#endif
