public class fib {

    public static int fib(int i){

         if (i < 2) return i;
         return fib(i - 2) + fib(i - 1);

    }

    public static void main (String[] args) {

        System.out.println(fib(46));

    }

}