package FPinScala.datastructures

sealed trait List[+A]
case object Nil extends List[Nothing]
case class Cons[+A](head: A, tail: List[A]) extends List[A]

object List {
  def tail[A](lst: List[A]): List[A] = lst match {
    case Nil => Nil
    case Cons(_, xs) => xs
  }

  def foldRight[A,B](as: List[A], z: B) (f: (A,B) => B):B =
    as match {
      case  Nil => z
      case Cons(x, xs) => f(x, foldRight(xs, z)(f))
    }

  def sum(ints: List[Int]): Int = ints match {
    case Nil => 0
    case Cons(x, xs) => x + sum(xs)
  }

  def product(ds: List[Double]): Double = ds match {
    case Nil => 1.0
    case Cons(0.0, _) => 0.0
    case Cons(x, xs) => x * product(xs)
  }

  def apply[A](as: A*): List[A] = {
    if (as.isEmpty)
      Nil
    else
      Cons(as.head, apply(as.tail: _*))
  }

}

sealed  trait  Tree[+A]
case class Leaf[A] (value:A) extends Tree[A]
case class Branch[A] (left: Tree[A], rithg: Tree[A] ) extends Tree[A]

object  Tree {
  def size[A](t: Tree[A]):Int = t match {
    case Leaf(_) => 1
    case Branch(l, r) => 1 + size(l) + size(r)
  }

  def maximum[A](t:Tree[A]):Int = t match {
    case Leaf(_) => 0
    case Branch(l, r) => maximum(l) max maximum(r)
  }

  def map[A,B](t: Tree[A])(f: A=>B):Tree[B] = t match  {
    case Leaf(a) => Leaf(f(a))
    case Branch(l, r) => Branch(map(l)(f), map(r)(f))
  }

  def depth[A](t:Tree[A]):Int = t match {
    case Leaf(_) => 0
    case Branch(l,r) => 1 + (depth(l) max depth(r))
  }

}

