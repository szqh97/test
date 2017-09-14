#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "luaerror.h"

void stackDump(lua_State *L) {
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top;++i) {
        int t = lua_type(L, i);
        switch(t) {
            case LUA_TSTRING:
                printf("'%s'", lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:
                printf(lua_toboolean(L, i) ? "true": "falsee");
                break;
            case LUA_TNUMBER:
                printf("'%g'", lua_tonumber(L, i));
                break;
            default:
                printf("'%s'", lua_typename(L, i));
                break;
        }
        printf(" ");
    }
    printf("\n");
}

int getfield(lua_State *L, const char* key) {
    int result;
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    //lua_gettfield(L, -1, key);
    if (!lua_isnumber(L, -1))
        error(L, "invalid componet in background");
    result = (int) lua_tonumber(L, -1) ;
    lua_pop(L, 1);
    return result;


}
void load(char* filename, int *width, int *height){
    lua_State *L = lua_open();
    luaL_openlibs(L);
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
        return ;
        //error(L, "cannot run configuration file: %s", lua_tostring(L, -1));
    lua_getglobal(L, "width");
    lua_getglobal(L, "height");
    lua_getglobal(L, "background");
    if (!lua_istable(L, 3)) {
        error(L, "'background' is not a table");
    }
    if (!lua_isnumber(L, 1))
        printf("`width` should be a number\n");

    if (!lua_isnumber(L, 2))
        printf("`height` should be a number\n");
    

    *width = (int)lua_tonumber(L, 1);
    *height = (int)lua_tonumber(L, 2);
    int red = getfield(L, "r");
    int green = getfield(L, "g");
    int blue = getfield(L, "b");

    printf("r:%d, g:%d, b:%d", red, green, blue);

    stackDump(L);
    lua_close(L);
}



int main(int argc , char* argv[])
{
    int w = -1;
    int h = -1;
    load(argv[1], &w, &h);
    
    printf("w is %d, h is %d\n", w, h);
    return 0;
}
