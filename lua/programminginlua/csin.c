#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <math.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int l_sin(lua_State *L) {
    double d = lua_tonumber(L, 1);
    lua_pushnumber(L, sin(d));
    return 1;
}

static int l_add(lua_State *L) {
    int a = lua_tonumber(L, -1);
    int b  = lua_tonumber(L, -2);
    printf("%d, %d\n", a, b);
    lua_pushnumber(L, a + b );
    return 1;
}
static int l_dir(lua_State* L) {
    DIR *dir;
    struct dirent *entry;
    int i;
    const char *path = luaL_checkstring(L, 1);
    dir = opendir(path);
    if (dir == NULL) {
        lua_pushnil (L);
        lua_pushstring(L, strerror(errno));
        return 2;
    }
    lua_newtable(L);
    i = 1;
    while ((entry = readdir(dir)) != NULL) {
        lua_pushnumber(L, i++);
        lua_pushstring(L, entry->d_name);
        lua_settable(L, -2);
    }
    closedir(dir);
    return 1;
}

static int l_map (lua_State *L) {
    int i , n;
    luaL_checktype(L, 1, LUA_TTABLE); // 第一个参数是一个table(t)
    luaL_checktype(L, 2, LUA_TFUNCTION); // 第二个参数是个函数
    n = lua_objlen(L, 1); //获取table的大小
    for (i = 1; i <= n; i++) {
        lua_pushvalue(L,2); //压入f 
        lua_rawgeti(L,1,i); // 压入 t[i]
        lua_call(L, 1,1); // 调用 f (t[i])
        lua_rawseti(L, 1, i); // t[i] = result
    }
    return 2;
}

static int l_split(lua_State *L) {
    const char *s = luaL_checkstring(L, 1);
    const char *sep = luaL_checkstring(L, 2);
    const char *e;
    int i = 1;

    lua_newtable(L); //结果
    //遍历所有分隔符
    while((e = strchr(s, *sep)) != NULL) {
        lua_pushlstring(L, s, e-s); //压入子串
        lua_rawseti(L, -2, i++);
        s = e + 1; // 跳过分隔符
    }
    
    //压入最后一个子串
    lua_pushstring(L, s);
    lua_rawseti(L, -2, i);
    return 1;
}

static int str_upper(lua_State *L) {
    size_t l;
    size_t i;
    luaL_Buffer b;
    const char *s = luaL_checklstring(L, 1, &l);
    luaL_buffinit(L, &b);
    for(i = 0; i < l; i++) {
        luaL_addchar(&b, toupper((unsigned char)(s[i])));
    }
    luaL_pushresult(&b);
    return 1;
}

static const struct luaL_Reg libcsin[]  = {
    {"l_sin", l_sin},
    {"l_dir", l_dir},
    {"l_add", l_add},
    {"l_map", l_map},
    {"l_split", l_split},
    {"str_upper", str_upper},
    {NULL, NULL}
};


int luaopen_libcsin(lua_State* L)
{
    const char* libName = "libcsin";
    luaL_register(L, libName, libcsin);

    return 1;
}

