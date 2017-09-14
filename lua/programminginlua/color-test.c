#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "luaerror.h"

struct ColorTable {
    char *name;
    unsigned int red, green, blue;
} colortable[] = {
    {"WHITE", 255, 255, 255},
    {"RED", 255, 0, 0},
    {"GREEN", 0, 255, 0},
    {"BLUE", 0, 0, 255},
    {NULL, 0, 0, 0}
};

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

void setfield(lua_State *L, const char* index, int value) {
    lua_pushstring(L, index);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}
void setcolor(lua_State *L, struct ColorTable* ct) {
    lua_newtable(L);
    setfield(L, "r", ct->red);
    setfield(L, "g", ct->green);
    setfield(L, "b", ct->blue);
    lua_setglobal(L, ct->name);
}

void load(char* filename) {
    lua_State *L = lua_open();
    luaL_openlibs(L);
    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
        return ;

    lua_getglobal(L, "background");
    if (!lua_istable(L, -1)) {
        error(L, "'background' is not a table");
    }

    int red = getfield(L, "r");
    int green = getfield(L, "g");
    int blue = getfield(L, "b");

    printf("r:%d, g:%d, b:%d", red, green, blue);

    int i = 0; 
    while(colortable[i].name != NULL) {
        setcolor(L, &colortable[i++]);
    }


}

int main(int argc , char* argv[])
{
    load(argv[1]);
    
    return 0;
}
