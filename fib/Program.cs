// See https://aka.ms/new-console-template for more information
Console.WriteLine("Hello, World!");
Fiby ff = new ();
Console.WriteLine("fib = {0}\nCount = {1}", ff.fib(46), ff.count);

class Fiby
{
    public long count;
    public long fib(long f)
    {
        this.count += 1;
        if (f < 2) return f;
        return this.fib(f - 1) + this.fib(f - 2);
    }
    public Fiby() { count = 0; } 
}
