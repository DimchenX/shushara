// See https://aka.ms/new-console-template for more information
long fib(long i) {
  if (i < 2) return i;
  return fib(i - 2) + fib(i - 1);
}
Console.WriteLine("\nFib = {0}\n", fib(46));
Console.WriteLine("Hello, World!");
