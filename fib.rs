static mut cnt: u64 = 0;

fn fib(i:i64) -> i64
{
  unsafe {
    cnt += 1;
  } 
   if i < 2 {return i;}
   return fib(i-1) + fib(i-2);
}

fn main()
{
   println!("fib = {}", fib(46));
   unsafe {
     println!("count = {}", cnt);
   }
}
