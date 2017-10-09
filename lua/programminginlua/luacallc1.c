#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

static int add2(lua_State* L) {
    double op1 = luaL_checknumber(L, 1);
    double op2 = luaL_checknumber(L, 2);
    lua_pushnumber(L, op1 + op2);
    return 1;
}

static int sub2(lua_State* L) {
    double op1 = luaL_checknumber(L, 1);
    double op2 = luaL_checknumber(L, 2);
    lua_pushnumber(L, op1 - op2);
    return 1;
}

static int l_dir(lua_State* L) {
    DIR *dir;
    struct dirent *entry;
    int i;
    const char *path = luaL_checkstring(L, 1);

    dir = opendir(path);
    if (dir == NULL) {
        lua_pushnil(L);
        lua_pushstring(L, strerror(errno));
        return 2;
    }
    lua_newtable(L);
    i = 1;
    while((entry = readdir(dir)) != NULL) {
        lua_pushnumber(L, i++);
        lua_pushstring(L, entry->d_name);
        lua_settable(L, -3);
    }

    closedir(dir);
    return 1;
}

const char* testfunc = "print(add2(1.0, 20.0)); print(sub2(20.0, 1.9)); print (l_dir(\".\"))";

int main()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "add2", add2);
    lua_register(L, "sub2", sub2);
    lua_register(L, "l_dir", l_dir);
    if (luaL_dostring(L, testfunc))
        printf("Failed to invoke.\n");
    lua_close(L);
    return 0;
}
