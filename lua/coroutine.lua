co1 = coroutine.create(function() print ("hi") end)
co2 = coroutine.create(function() print ("hi") end)
print(co1)
print(co2)
print(coroutine.status(co1))
print(coroutine.status(co2))
coroutine.resume(co1)
coroutine.resume(co2)
print(coroutine.status(co1))
print(coroutine.status(co2))

print ('-----------------------')
co = coroutine.create(function() 
        for i = 1, 10 do 
            print("co", i)
            coroutine.yield()
        end
    end)

for i=1,10 do
    
    coroutine.resume(co)
    print(coroutine.status(co))
end
    coroutine.resume(co)
    print(coroutine.status(co))
coroutine.resume(co)
coroutine.resume(co)
