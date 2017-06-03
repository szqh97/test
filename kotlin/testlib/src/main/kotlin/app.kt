/**
 * Created by szqh97 on 17-5-27.
 */
import tclass.*
import SmartCast.*
import TCollect.*
import strings.*
fun main(args: Array<String>) {
    fun test(){
        println("Hello ${if (args.size > 0) args[0] else "SomeOne"}")
        testPerson()
        rectangeltest()
        val rect = createRandomRectangle()
        println(rect.height)
        println(rect.width)
        println(rect.isSquare)

        println(getMnemonic(Color.VIOLET))
        println(getWarmth(Color.ORANGE))
        println(mix(Color.RED, Color.YELLOW))
        println(eval(Sum(Num(1), Num(2))))
        println(eval2(Sum(Num(1), Num(2))))
        evalWithLoggin(Sum(Num(1), Num(2)))

        testIteratingMap()
        testCollection()
        val strings: List<String> = listOf("first", "second", "fourteen")
        println(strings.last())
    }
    test()
    val sb = StringBuilder("Kotlin?")
    sb.lastChar = '!'
    println(sb)


}