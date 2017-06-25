package FPinScala


/**
  * Created by li_yun on 2017/6/23.
  */
import Ch03._
//import FPinScala.datastructures._

object Ch03test extends  App{
  /*
  val x = List(1,2,3,4,5) match {
    case Cons(x, Cons(2, Cons(4,_))) => x
    case Nil => 42
    case Cons(x, Cons(y, Cons(3,Cons(4,_)))) => x + y
    //case Cons(h, t) => h + sum(t)
    case _ => 101
  }

  println(x)
  val ex1: List[Double] = Nil
  val ex2: List[Int] = Cons(1, Nil)
  val ex3: List[String] = Cons("a", Cons("b", Nil))
  println(ex3)

*/
  var lst: List[Int] = List(1,2,3,4,5,6,7)
  println(reverse(lst))
  println(length(lst))
  println(init(lst))
  println(dropWhile(lst, (x:Int)=>x==5))
  println("---")
  println(setHead(lst,111))

  println(drop(lst, 3))


}
