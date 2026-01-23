function fib(i)
{
  if (i < 2) {
     return i;
  }
  return fib(i - 2) + fib (i - 1);
}

console.log(fib(46));
