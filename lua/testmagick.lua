#!/usr/bin/env lua
local magick = require "magick"
local img = assert(magick.load_image("/Users/li_yun/Downloads/p7.jpg"))
img:strip()
print("width:", img:get_width(), "height:", img:get_height());
img:write("/tmp/out.jpg")
local img2 = assert(magick.load_image("t.png"))
img2:resize(300,497)
img2:write("tt.png")
