local keys = redis.call('keys', KEYS[1])

for k, v in ipairs(keys) do
    redis.call('del', v)
end
