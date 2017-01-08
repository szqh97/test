local s_more = require("s_more")

print(s_more.upper("while"))
print(s_more.lower("hello"))

local url = require("urlendecode")

local u = url:new()
local ss = u:encode('===')
print (ss)
print (u:encode('东家'))
print (u:decode('%E4%B8%9C'))
print (s_more.db_name)
