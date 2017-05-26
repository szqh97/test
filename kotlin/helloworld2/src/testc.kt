/**
 * Created by szqh97 on 17-5-26.
 */
package testc

import com.sun.org.apache.xpath.internal.operations.Bool

class Address {
    var name: String = "name"
        set(value) {
            field = value
        }
    var street: String = "street"
    var city: String = "city"
    var state: String? = "state"
    var zip: String  = "zip"

}

fun copyAddress(address:Address): Address {
    val result = Address()
    result.name = address.name
    result.street = address.street
    result.city = address.city
    result.state = address.state
    result.zip = address.zip
    return result
}

interface MyInterface {
    val prop: Int
    val propertyWithImplementation: String
        get() = "foo"
    fun foo() {
        println(prop)
    }
}

class Child: MyInterface {
    override val prop: Int = 29
}

interface A {
    fun foo() {println("A")}
    fun bar()
}

interface B {
    fun foo() {println("B")}
    fun bar() {print("bar")}
}

class C:A {
    override fun bar() {println("bar")}
}

class D: A, B {
    override fun foo () {
        super<A>.foo()
        super<B>.foo()()
    }

    override fun bar() {
        super<B>.bar()
    }
}

