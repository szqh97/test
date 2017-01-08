local _M = {}
local mt = {__index = _M}
function _M.upper(s)
    return string.upper(s)
end
return _M
