/**
  * Created by li_yun on 2017/6/23.
  *
  */

package FPinScala{

  object Ch02 {
    private def abs(n: Int) = if (n < 0) -n else n

    private def formatAbs(x: Int) = {
      val msg = "The absolute of %d is %d"
      msg.format(x, abs(x))
    }

    def factorial(n: Int): Int = {
      @annotation.tailrec
      def go(n: Int, acc: Int): Int =
        if (n <= 0) acc
        else go(n - 1, n * acc)

      go(n, 1)
    }

    def fibonacci(n: Int): Int = {
      @annotation.tailrec
      def tailFibonacci(n: Int, r1: Int, r2: Int): Int = {
        if (n == 0)
          r1
        else
          tailFibonacci(n - 1, r2, r1 + r2)
      }

      tailFibonacci(n, 0, 1)
    }

    private def formatFactorial(x: Int) = {
      val msg = "The factorial of %d is %d"
      msg.format(7, factorial(7))
    }

    def formatResult(name: String, n: Int, f: Int => Int) = {
      val msg = "The %s of %d is %d"
      msg.format(name, n, f(n))
    }

    def findFirstStringArray(ss: Array[String], key: String): Int = {
      @annotation.tailrec
      def loop(n: Int): Int = {
        if (n > ss.length) -1
        else if (ss(n) == key) n
        else loop(n - 1)
      }

      loop(0)
    }

    def findFirst[A](as: Array[A], p: A => Boolean): Int = {
      def loop(n: Int): Int = {
        if (n >= as.length) -1
        else if (p(as(n))) n
        else loop(n + 1)
      }

      loop(0)
    }

    def normalFabonacci(n: Int): Int = {
      if (n == 0) 0
      else if (n == 1) 1
      else
        normalFabonacci(n - 1) + normalFabonacci(n - 2)
    }

    def isSorted[A](as: Array[A], ordered: (A, A) => Boolean): Boolean = {
      @annotation.tailrec
      def loop(n: Int, s: Boolean): Boolean = {
        if (n == as.length - 1) s
        else loop(n + 1, s && ordered(as(n), as(n + 1)))
      }

      loop(0, true)
    }

    val sortFunc = (a: Int, b: Int) => a <= b

    def partial[A, B, C](a: A, f: (A, B) => C): B => C = {
      (b: B) => f(a, b)
    }

    def curry[A, B, C](f: (A, B) => C): A => (B => C) = {
      //(a:A)=>partial(a, f)
      (a: A) => (b: B) => f(a, b)
    }

    // blocked by uncurry?
    def uncurry[A, B, C](f: A => B => C): (A, B) => C = {
      (a: A, b: B) => f(a)(b)
    }

    def compose[A, B, C](f: B => C, g: A => B): A => C = {
      (a: A) => f(g(a))
    }

  }

}
