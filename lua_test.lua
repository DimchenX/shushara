print(arg[-1])

local rfile = io.open(arg[0], "r")
local data = rfile:read(1024) 
rfile:close()

print(data, string.format("\nData size: %3d\n", #data))

local function fib(i)
	if (i<2) then 
		return i 
	end
	return fib(i-2) + fib(i-1)  
end

print("fib =", fib(46))
