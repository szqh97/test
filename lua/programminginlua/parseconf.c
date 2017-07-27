#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void load(char* filename, int *width, int *height)
{
    lua_State *L = lua_open();
    luaL_openlibs(L);

    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
        return ;
        //error(L, "cannot run configuration file: %s", lua_tostring(L, -1));
    lua_getglobal(L, "width");
    lua_getglobal(L, "height");
    if (!lua_isnumber(L, -2))
        printf("`width` should be a number\n");

    if (!lua_isnumber(L, -1))
        printf("`height` should be a number\n");
    
    *width = (int)lua_tonumber(L, -2);
    *height = (int)lua_tonumber(L, -1);
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
