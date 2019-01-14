#!/usr/bin/env lua

local csin = require "libcsin"
print (csin.l_sin(1))
print (csin.l_add(11, 22))
--print (csin.l_dir("."))
--
--
-- test l_map
function test (i)
    print ("test")
    return "12|" .. i
end
 tt = {1,2,3,4}
 out = csin.l_map(tt, test)
 for idx,val in pairs(out) do
     
     print ( "at ".. idx .. " is: " .. val )
 end

-- test str_upper
print(csin.str_upper("abckdefFFF"))
 
--- tes l_split
 
sout = csin.l_split("testekeb", "e")
for idx,val in ipairs(sout) do
    print ("l_split at " .. idx .. " is :" .. val)
 end


