Set.mt = {}
function Set.new(t)
    local set = {}
    setmetatable(set, Set.mt)
    for _,l in ipairs(t) do
        set[l] = true
    end
    return set
end
