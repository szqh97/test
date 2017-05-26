/**
 * Created by szqh97 on 17-5-26.
 */

import testc.*

fun testbreak (){
    loop@ for (i in 1 .. 100) {
        for (j in 1 .. 100) {
            if (i * j > 100) break@loop
            println (i *j )
        }

    }
}

class Invoice
class Customer (name: String) {
    init {
        println("Customer initilized with value ${name}")
    }
    val customerKey = name.toUpperCase()
}
open class Base (p: Int) {
    open fun v() {
    }
    fun nv () {}
}
class Derived(p: Int) : Base(p) {
    override fun v () {}
}

open class AnotherDerived(p: Int) : Base(p) {
    final override fun v() {}
}

interface Foo {
    val count: Int
}

open class A {
    open fun f() {print("A")}
    fun a() {print("a")}
}

interface B {
    fun f() {print("B")}
    fun b() {print ("b")}
}

class C():A(), B {
    override fun f() {
        super<A>.f()
        super<B>.f()
    }
}

class Bar1(override  val count: Int) : Foo
class Bar2: Foo {
    override var count: Int = 0
}
fun main(args: Array<String>) {
    testbreak()
    val invoice = Invoice()
    val customer = Customer("Joe Smith")
    val d = Derived(11)

    val c = C()
    c.f()

    println()
    val address = Address()
    address.name = "test"
    println(address.name)
    val b = copyAddress(address )
    println(b.zip)

    val child = Child()
    println(child.prop)
    child.foo()

}
