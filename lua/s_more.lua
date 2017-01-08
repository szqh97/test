local s_base = require("s_base")
local _M = {}
_M = setmetatable(_M, {__index = s_base})

function _M.lower(s)
    return string.lower(s)
end
_M.db_name = "kk"

return _M
