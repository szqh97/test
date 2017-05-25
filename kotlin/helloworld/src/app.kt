/**
 * Created by li_yun on 2017/5/25.
 */
fun sum(a: Int, b: Int): Int {
    return a + b
}
fun sumk(a: Int, b: Int) = a + b
fun maxOf(a: Int, b: Int): Int {
    if (a > b ) {
        return a
    } else {
        return b
    }
}
fun maxofif(a:Int, b:Int) = if (a > b) a else b

fun parseInt(a: String) = a.toIntOrNull()

fun printProduct(a:String, b:String) {
    val x = parseInt(a)
    val y = parseInt(b)
    if (x != null && y != null) {
        println(x*y)
    } else {
        println("either '$a' or '$b' is not a number")
    }
}

fun getStringLength(obj: Any) = if (obj is String) obj.length else null
fun printLength(obj: Any) {
    println("$obj string length is ${getStringLength(obj) ?: "... err, not a string"} ")
}

fun fortest() {
    val items = listOf("hello", "this " , "is")
    for (i in items) {
        println(i)
    }
    for (index in items.indices) {
        println("item at $index is ${items[index]}")
    }
}

fun describe(obj: Any): String =
        when(obj) {
            1               -> "One"
            "Hello"         -> "Greeting"
            is Long         -> "Long"
            !is String      -> "Not a String"
            else            -> "unko"
        }

fun rangetest() {
    val x = 10
    val y = 9
    if (x in 1..y+1) {
        println( "x is in fits")
    }
}

fun filterfruits() {
    val fruits = listOf("banana", "avocado", "apple", "kiwi")
    fruits
    .filter{it.startsWith("a")}
    .sortedBy { it }
    .map { it.toUpperCase() }
    .forEach {println(it)}
}

fun main(args: Array<String>) {
 // println("hello world")
 // println(sum(11,23))
 // println(sumk(11,23))
 // println(maxOf(11,23))
 // println(maxofif(111,222))
 // printProduct("111", "333")
 // printLength("Incomprehensibilities")
 // printLength(1000)
 // fortest()
 // println(describe(1))
    rangetest()
    filterfruits()
}