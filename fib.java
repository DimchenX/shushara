public class fib {

public static long cnt = 0;

public static long fib(long i) {
 cnt ++;
 if(i < 2) return i;
 return fib(i - 2) + fib(i - 1);
}

public static void main (String[] args) {
 System.out.println("fib = " + fib(46) + "\ncounts = " + cnt + "\n");
}
}