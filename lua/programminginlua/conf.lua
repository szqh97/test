#!/usr/bin/env lua
local os = require "os"
if os.getenv("DISPLAY") == ":0.0" then
    width = 20
    height = 30
else 
    width = 200
    height = 300
end

background = {r=1,g=2,b=3}

function f(x, y)
    return x *y
end
