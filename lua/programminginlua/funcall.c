#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "luaerror.h"
#include "luaerror.h"
#include <stdarg.h>
#include <string.h>

double f (lua_State* L, double x, double y) {
    double z;
    lua_getglobal(L, "f");
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    if (lua_pcall(L, 2, 1, 0) != 0 ) {
        error(L, "error running function 'f', %s", lua_tostring(L, -1));
    }
    if (!lua_isnumber(L, -1)) {
        error(L, "function 'f' must return a number");
    }
    z = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return z;
}
void  call_va(lua_State* L, const char* func, const char* sig, ...)
{
    va_list vl;
    int narg, nres;
    va_start(vl, sig);
    lua_getglobal(L, func);
    // push args
    for(narg = 0; *sig; narg++) {
        luaL_checkstack(L, 1, "too many arguments");
        switch (*sig++) {
            case 'd':
                lua_pushnumber(L, va_arg(vl, double));
                break;
            case 'i':
                lua_pushinteger(L, va_arg(vl, int));
                break;
            case 's':
                lua_pushstring(L, va_arg(vl, char *));
                break;
            case '>':
                goto endargs;
            default:
                error(L, "invalid option(%c", *(sig -1));
                
        }
    }
endargs:
    nres = strlen(sig);
    if (lua_pcall(L, narg, nres, 0) != 0) {
        error(L, "error calling '%s':%s", func, lua_tostring(L, -1));
    }
    // check result.
    nres = -nres;
    while(*sig) {
        switch(*sig++) {
            case 'd':
                if (!lua_isnumber(L, nres)){
                    error(L, "wrong result type");
                }
                *va_arg(vl, double*) = lua_tonumber(L, nres);
                break;
            case 'i':
                if (!lua_isnumber(L, nres)) {
                    error(L, "wrong result type");
                }
                *va_arg(vl, int*) = lua_tointeger(L, nres);
                break;
            case 's':
                if (!lua_isstring(L, nres)) {
                    error(L, "wrong result tyep");
                }
                *va_arg(vl, const char**) = lua_tostring(L, nres);
                break;
            default:
                error(L, "invalid option(%c)", *(sig-1));
        }
        nres++;
    }
    
    va_end(vl);

}

void load(char* filename) {
    lua_State *L = lua_open();
    luaL_openlibs(L);
    if (luaL_loadfile(L, filename)|| lua_pcall(L, 0,0,0)) {
        return;
    }

    double z = 0.0;
    call_va(L, "f", "dd>d", 1.0,2.0, &z);
    /*
    lua_getglobal(L, "f");
    lua_pushnumber(L, 1.0);
    lua_pushnumber(L, 2.0);
    if (lua_pcall(L, 2, 1, 0) != 0) {
        error(L, "error running function 'f', %s , %d", lua_tostring(L, -1), 0 );
    }
    if (!lua_isnumber(L, -1)) {
        error(L, "function 'f' must return a number");
    }
    z = lua_tonumber(L, -1);
    lua_pop(L, 1);
    */

    
    lua_close(L);
    printf("z is %f", z);

}


int main(int argc , char* argv[])
{
    load(argv[1]);
    
    return 0;
}
