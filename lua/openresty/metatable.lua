local set1 = {10, 20, 30}
local set2 = {20, 40, 50}

local union = function (self, another)
    local set = {}
    local result = {}

    for i, j in pairs(self) do
        set[j] = true 
    end
    for i, j in pairs(another) do
        set[j] = true
    end

    for i,j in pairs(set) do
        table.insert(result, i)
    end
    return result
end

setmetatable(set1, {__add=union})

local set3 = set1 + set2
for _, val in pairs(set3) do
    io.write(val .. " ")
    
end


arr = {1, 2, 3, 4, 5}

arr = setmetatable(arr, {__tostring = function (self)
    local result = '{'
    local sep = ''
    for _,val in pairs(self) do
        result = result .. sep .. val
        sep = ','
    end

    result = result .. '}'
    return result
end})
print("\n")

print(arr)

-----
functor = {}
function func1(self, args)
    print("call from ", arg)
end
    
setmetatable(functor, {__call=func1})
functor("kkk")
print(functor)


mytable = setmetatable({key1 = "value1"},
{__index = function (self, key)
    if key == "key2" then
        return "llllllll"
    else
        return 'MMMM'
    end
end
})

print(mytable.key1, mytable.key2)
