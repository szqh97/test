local name = ngx.var.name
local len = string.len(name)
local headers = ngx.req.get_headers()

if len < 18 then
    ngx.log(ngx.ERR, "filename[",name,"] error")
    ngx.exit(ngx.HTTP_NOT_FOUND)
end
function dir_exists(path)
    local file = io.open(path, "rb")
    if file then file:close() end
    return file ~= nil
end
function saveFile(path, content)
    local file = io.open(path, "w")
    if nil ~= file then
        file:write(content)
        file:close()
    else
        ngx.log(ngx.ERR, "write file: " .. path .. " failed")
    end
end
local mimeType = 'image/jpeg'
local types = {
    ["jpeg"] = "image/jpeg", ["jpg"] = "image/jpeg", ["gif"] = "image/gif", ["png"] = "image/png",
    ["js"] = "application/x-javascript", ["css"] = "text/css",["json"] = "application/json"
}
local m, err = ngx.re.match(name , "([\\w\\.]{18})(\\.(gif|jpeg|jpg|png|js|css|json))?(_(\\d+)x(\\d+))?$")
local sf = "/v1/tfs/"
local res = nil
local tmp = nil
if m then
    if nil ~= m[3] then
        ngx.header.content_type = (types[m[3]] and types[m[3]]) or mimeType
    else
        ngx.header.content_type = mimeType
    end
    if nil == m[4] then
        res = ngx.location.capture(sf..name)
        if res.status ~= 200 then
            ngx.log(ngx.ERR, "get source file[", name, "] error")
            ngx.exit(ngx.HTTP_NOT_FOUND)
        end
        local body = res.body
        local magick = require "magick"
        local img = magick.load_image_from_blob(res.body)
        if img == nil then
            tmp, err = ngx.print(body)
            ngx.eof()
            if not dir_exists(ngx.var.dp) then
                local lfs = require "lfs"
                lfs.mkdir(ngx.var.dp)
            end
            saveFile(ngx.var.fp, res.body)
            ngx.exit(ngx.HTTP_OK)
        end

        local img_type = img:get_format()
        if img_type == "jpeg" or img_type == "jpg" then
            img:set_quality(75)
            body = img:get_blob()
            img:destroy()
        elseif img_type == "png" then
            img:destroy()
            ngx.header.content_type = "image/png"

            if not dir_exists(ngx.var.dp) then
                local lfs = require "lfs"
                lfs.mkdir(ngx.var.dp)
            end

            local tmppng = os.tmpname()
            local wp = io.open(tmppng, 'w')
            wp:write(body)
            wp:flush()
            wp:close()

            local ffi = require "ffi"
            local pngquant = ffi.load("pngquant")
            ffi.cdef [[
            int pngquant_file(const char* filename, const char* outname);
            ]]
            local r = pngquant.pngquant_file(tmppng, ngx.var.fp)
            os.remove(tmppng)
            if tonumber(r) == 0 and dir_exists(ngx.var.fp) then
                local rf = io.open(ngx.var.fp, "rb")
                local len = rf:seek("end")
                rf:seek("set", 0)
                body = rf:read(len)
                rf:close()
                temp, err = ngx.print(body)
                ngx.eof()
                ngx.exit(ngx.HTTP_OK)
            else
                ngx.log(ngx.ERR, "pngquant error: " .. tonumber(res) .. " or filename: " .. ngx.var.fp .. " not exists")
            end

        end

        tmp, err = ngx.print(body)
        ngx.eof()
        if not dir_exists(ngx.var.dp) then
            local lfs = require "lfs"
            lfs.mkdir(ngx.var.dp)
        end
        saveFile(ngx.var.fp, res.body)
        ngx.exit(ngx.HTTP_OK)      -- get source file
    end
    if nil == m[2] then
        m[2] = ''
    end
else
    ngx.log(ngx.ERR, "filename[",name,"] match error")
    if err then
        ngx.log(ngx.ERR, "match error: ", err)
        return
    end
    ngx.exit(ngx.HTTP_NOT_FOUND)
end
res = ngx.location.capture(sf..m[1]..m[2])
if res.status ~= 200 then
    ngx.log(ngx.ERR, "get source file[", m[1]..m[2], "] error")
    ngx.exit(ngx.HTTP_NOT_FOUND)
end
local magick = require "magick"
local img = assert(magick.load_image_from_blob(res.body))
local ow, oh = img:get_width(), img:get_height()
local imgtype = img:get_format()
local w = tonumber(m[5])
local h = tonumber(m[6])
if w < ow and h < oh then
    img:resize(w,math.ceil(oh*w/ow))
end
img:set_quality(75)
local str = img:get_blob()

if imgtype == "png" then
    ngx.header.content_type = "image/png"
    if not dir_exists(ngx.var.dp) then
        local lfs = require "lfs"
        lfs.mkdir(ngx.var.dp)
    end
    local temp_png = os.tmpname()
    img:write(temp_png)
    img:destroy()
    local ffi = require "ffi"
    local pngquant = ffi.load("pngquant")
    ffi.cdef [[
    int pngquant_file(const char* filename, const char* outname);
    ]]

    local res = pngquant.pngquant_file(temp_png, ngx.var.fp)
    os.remove(temp_png)
    if tonumber(res) == 0 and dir_exists(ngx.var.fp) then
        local rf = io.open(ngx.var.fp, "rb")
        local len = rf:seek("end")
        rf:seek("set", 0)
        str = rf:read(len)
        rf:close()
    else
        ngx.log(ngx.ERR, "pngquant error:" .. tonumber(res) .. " or filename: "  .. ngx.var.fp .. "not exists")
    end
end


local res , err = ngx.print(str)
ngx.eof()

if not dir_exists(ngx.var.dp) then
    ngx.log(ngx.ERR, "dir[", ngx.var.dp, "] not exsits")
    local lfs = require "lfs"
    lfs.mkdir(ngx.var.dp)
end

if imgtype ~= "png" then
    img:write(ngx.var.fp)
    img:destroy()
end
img:destroy()


ngx.exit(ngx.HTTP_OK)
