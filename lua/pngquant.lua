local ffi = require ("ffi")
local pngquant = ffi.load("pngquant")
ffi.cdef [[
pngquant_error pngquant_file(const char* filename, const char* outname);
]]
local res = pngquant.pngquant_file("./t.png", "./ttt.png")
print (res)

