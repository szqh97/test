#!/usr/bin/env lua
local a = {1, 3, 5, "hello"}
print(table.concat(a))
print(table.concat(a, "|"))

local a = {1, 8}
table.insert(a, 1, 3)
print(a)

local b = {}
b[-2] = 1
b[-1] = 0
print(#b)
print(table.getn(b))
