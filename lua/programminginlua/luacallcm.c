#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

//extern "C"{ 
int add (lua_State *L) 
{
    double op1 = luaL_checknumber(L, 1);
    double op2 = luaL_checknumber(L, 2);
    lua_pushnumber(L, op1 + op2);
    return 1;
}

 int sub (lua_State *L)
{
    double op1 = luaL_checknumber(L, 1);
    double op2 = luaL_checknumber(L, 2);
    lua_pushnumber(L, op1 - op2);
    return 1;
}
//}

struct luaL_Reg testlibs[] = {
    {"add", add},
    {"sub", sub},
    {NULL, NULL}
};


int luaupen_testlib(lua_State *L)
{
    const char* libName = "testlib";
    luaL_register(L, libName, testlibs);
    return 1;
}
