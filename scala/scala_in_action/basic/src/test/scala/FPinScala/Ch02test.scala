package FPinScala

/**
  * Created by li_yun on 2017/6/23.
  */
import Ch02.findFirst
import Ch02._

object Ch02test extends App {
  println(findFirst(Array(1,2,3,4,5), (x:Int)=>x==3))
  println(formatResult("test", 4, factorial))

  val f = (x:Double) => math.Pi / 2 - x

}
