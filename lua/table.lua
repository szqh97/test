#!/usr/bin/env lua
local corp  = {
    web = "www.google.com",
    telephone = "12345678",
    staff = {"Jack", "Scott", "Gary"},
    100876,
    100191,
    [10] = 360,
    ["city"] = "Beijing"
}

print(corp.web)
print(corp["telephone"])
print(corp[2])
print(corp["city"])
print(corp.staff[1])
print(corp[10])

print(table.getn(corp))
print(#corp)
local s = "kkkk"
print(#s)
