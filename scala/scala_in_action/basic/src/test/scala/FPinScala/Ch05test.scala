package FPinScala

/**
  * Created by li_yun on 2017/6/25.
  */

import Stream._
object Ch05test extends  App{

  val s:Stream[Int] = cons(1, cons(2,cons(3,(cons(4,empty)))))
  println(s.take(3))
}
