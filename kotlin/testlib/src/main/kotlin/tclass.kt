/**
 * Created by li_yun on 2017/5/30.
 */
package  tclass
import java.util.*

class  Person(
        val name:String,
        var isMarried: Boolean
)
class Rectangle (val height: Int, val width: Int) {
    val isSquare: Boolean
    get() {
        return height == width
    }
}
fun createRandomRectangle(): Rectangle
{
    val random = Random()
    return Rectangle(random.nextInt(), random.nextInt())
}
fun rectangeltest() {
    val rect = Rectangle(41,42)
    println(rect.isSquare)
}

fun testPerson() {
    val s  = Person("Bob", false)
    println(s.toString())
}

enum class Color (var r: Int, val g: Int, val b: Int) {
    RED (255,0,0),
    ORANGE(255,165,0),
    YELLOW(255,255,0),
    GREEN(0,255,0),
    BLUE(0,0,255),
    INDIGO(75,0,130),
    VIOLET(238,130,238);

    fun rgb() = (r * 256 + g) * 256 + b
}

fun getMnemonic(color: Color) =
        when (color) {
            Color.RED -> "Richard"
            Color.ORANGE -> "Of"
            Color.YELLOW -> "York"
            Color.GREEN -> "Gave"
            Color.BLUE -> "Battle"
            Color.INDIGO -> "In"
            Color.VIOLET -> "Vain"
        }

fun getWarmth(color: Color) =
        when (color) {
            Color.RED, Color.ORANGE, Color.YELLOW -> "warm"
            Color.GREEN -> "neutral"
            Color.BLUE, Color.INDIGO, Color.VIOLET -> "cold"
        }

fun mix(c1: Color, c2: Color) =
        when (setOf(c1, c2)) {
            setOf(Color.RED, Color.YELLOW) -> Color.ORANGE
            setOf(Color.YELLOW, Color.BLUE) -> Color.GREEN
            setOf(Color.BLUE, Color.VIOLET) -> Color.INDIGO
            else -> throw  Exception("Dirty Color")
        }

fun mixOptimized(c1: Color, c2: Color)  =
        when {
            (c1 == Color.RED && c2 == Color.YELLOW) || (c1 == Color.YELLOW && c2 == Color.RED) -> Color.ORANGE
            (c1 == Color.BLUE && c2 == Color.VIOLET) || (c1 == Color.VIOLET && c2 == Color.BLUE) -> Color.INDIGO
            (c1 == Color.YELLOW && c2 == Color.BLUE) || (c1 == Color.BLUE && c2 == Color.YELLOW) -> Color.GREEN
            else -> throw  Exception("Dirty color")
        }

fun testIteratingMap() {
    val binaryReps = TreeMap<Char, String>()
    for (c in 'A' .. 'F') {
        val binary = Integer.toBinaryString(c.toInt())
        binaryReps[c] = binary
    }

    for ((letter, binary) in binaryReps) {
        println("$letter = $binary")
    }
}
