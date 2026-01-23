def fib(n):
    if n < 2:
        return n
    return fib(n-2) + fib(n-1)

n = 46
print("fib(", n, ")= ", fib(n))
