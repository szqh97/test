#!/usr/bin/env lua

local ffi = require "ffi"
local myffi = ffi.load("myffi")

ffi.cdef[[
int add(int x, int y);
typedef struct Point{
    int x;
    int y;
} Point;

int pointAdd(Point* p);
]]

local res = myffi.add(1,2)
print (res)

local point
local
