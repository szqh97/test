package FPinScala

/**
  * Created by li_yun on 2017/6/23.
  */

object Ch03 {

  def tail[A](lst:List[A]):List[A] = lst match {
    case Nil => Nil
    case _ :: t => t
  }

  def setHead[A](lst: List[A], e: A): List[A] = lst match {
    case Nil => List[A](e)
    case _::t => e::t
  }

  @annotation.tailrec
  def drop[A](lst: List[A], n: Int): List[A] = {
    assert(n>=0)
    n match {
      case 0 => lst
      case 1 => tail (lst)
      case _ => drop(tail(lst), n-1)
    }
  }

  def dropWhile[A](lst: List[A], f: A => Boolean): List[A] = {
    lst
  }

  def init[A](lst: List[A]) : List[A] = {
    @annotation.tailrec
    def loop(m:List[A], n:List[A]):List[A] = {
      m match {
        case Nil => n
        case _ :: Nil => n
        case h:: t => loop(t, n:+h)
      }
    }
    loop(lst, Nil)

  }

  def foldRight[A,B](as:List[A], z:B) (f:(A,B)=>B):B = as match {
      case Nil => z
      case x::xs =>f(x, foldRight(xs, z)(f))
  }

  def length[A] (as: List[A]): Int = {
    foldRight(as,0)((_,s) => 1+s)
  }

  @annotation.tailrec
  def foldLeft[A,B](as: List[A], z:B) (f:(B,A)=>B):B = {
    as match {
      case Nil => z
      case h::t => foldLeft(t, f(z,h))(f)
    }
  }

  def reverse[A](l: List[A]):List[A] = {
    foldLeft(l, Nil: List[A])((x,y) => y :: x)
  }
}
