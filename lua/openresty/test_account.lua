#!/usr/bin/env lua
local account = require("account")
local a = account:new(1)
--a:deposit(100)
a:withdraw(1)
print(a.balance)
