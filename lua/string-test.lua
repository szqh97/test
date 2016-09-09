#!/usr/bin/env lua
local string = require("string")
print(string.byte("abc", 1, 3))
print(string.byte("abc", 3))
print(string.byte("abc"))
