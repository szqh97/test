#!/usr/bin/env lua
file = io.input("time.lua")
repeat
    line = io.read()
    if nil == line then
        break
    end
    print (line)
until (false)

io.close(file)

file = io.open("time.lua", "r")
for line in file:lines() do
    print(line)
end
file:close()
