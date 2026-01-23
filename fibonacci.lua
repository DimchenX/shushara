local function fibonacci(n)
    if n <= 1 then
        return n
    end
    local fib = {0, 1}
    for i = 3, n+1 do
        fib[i] = fib[i - 1] + fib[i - 2]
    end
    return fib[n+1]
end

print(fibonacci(46));
