package FPinScala.laziness
import Stream._

import scala.annotation.tailrec
trait Stream[+A] {

  def headOption: Option[A] = this match  {
    case Empty => None
    case Cons(h, _) => Some(h())
  }

  def toList: List[A] = {
    @annotation.tailrec
    def go(s: Stream[A], acc: List[A]): List[A] = s match {
      case _ => acc
      case Cons(h,t) => go(t(), h() :: acc)
    }
    go(this, List()).reverse
  }

  def take(n:Int):Stream[A] = this match {
    case Cons(h,_) if n == 1 => cons(h(), empty)
    case Cons(h,t) if n > 1 => cons(h(), t().take(n-1))
  }

  @annotation.tailrec
  final def drop(n:Int):Stream[A] = this match {
    case _ => this
    case Cons(_, t) if n > 0 => t().drop(n-1)
  }

  def drop2(n:Int): Stream[A] = {
    @annotation.tailrec
    def loop(s: Stream[A], n:Int): Stream[A] = s match {
      case _ => s
      case Cons(_, t) if n > 1 => loop(t(), n-1 )
    }
    loop(this, n)
  }

  def takeWhile(p: A=>Boolean): Stream[A] = this match {
    case Cons(h, t) if p(h()) => cons(h(), t() takeWhile p)
    case _ => empty
  }

  def foldRight[B](z: => B)(f: (A, => B) => B): B =
    this match {
      case Cons(h,t) => f(h(), t().foldRight(z)(f))
      case _ => z
    }

  def exists(p: A=>Boolean): Boolean =
    foldRight(false) ((a,b) =>p(a) || b)

  def forAll(p: A => Boolean): Boolean =
    foldRight(true)((a,b) => p(a) && b)

  def takeWhile_1(f: A => Boolean): Stream[A] =
    foldRight(empty[A]) ((h,t) =>
      if (f(h)) cons(h,t)
      else empty
    )

  def headOption_1: Option[A] =
    foldRight(None: Option[A])((h,_) => Some(h))

  def map[B](f: A => B): Stream[B] =
    foldRight(empty[B])((h,t) => cons(f(h),t))

  def filter(f: A => Boolean): Stream[A] =
    foldRight(empty[A])((h,t) =>
      if (f(h)) cons(h, t)
      else t
    )

  def append[B>:A](s: => Stream[B]): Stream[B] =
    foldRight(s)((h,t) => cons(h,t))

  def flatMap[B](f: A => Stream[B]): Stream[B] =
    foldRight(empty[B])((h,t) => f(h) append t)

}

case object Empty extends Stream[Nothing]
case class Cons[+A](h: ()=>A, t: ()=>Stream[A]) extends Stream[A]

object Stream {
  def cons[A] (hd: => A, tl: =>Stream[A]): Stream[A] = {
    lazy val head = hd
    lazy val tail = tl
    Cons(() => head, () => tail)
  }

  def empty[A]: Stream[A] = Empty

  def apply[A](as: A*): Stream[A] =
    if (as.isEmpty) empty
    else cons(as.head, apply(as.tail: _*))

  def constant[A](a:A):Stream[A] = {
    lazy val tail: Stream[A] = Cons(()=>a, ()=>tail)
    tail
  }

  def from(n:Int):Stream[Int] = {
    cons(n, from(n+1))
  }

  val fibs = {
    def go(f0:Int, f1:Int): Stream[Int] =
      cons(f0, go(f1, f0+f1))
    go(0,1)
  }

  def unfold[A, S](z: S)(f: S => Option[(A,S)]): Stream[A] =
    f(z) match {
      case Some((h,s)) => cons(h,unfold(s)(f))
      case None => empty
    }



}
object test extends App {

  val s = Stream(1,2,3,4,5)
  println(s.take(3).toList)
  Stream(1,2,3,4).map(_ + 10).filter(_ %2 == 0).toList
}