/**
 * Created by szqh97 on 17-5-27.
 */
import tclass.*
fun main(args: Array<String>) {
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


}