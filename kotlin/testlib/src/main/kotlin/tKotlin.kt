/**
 * Created by li_yun on 2017/6/2.
 */
package strings

fun String.lastChar(): Char = this.get(this.length - 1)
fun <T> Collection<T>.joinToString(
        separator: String = ", ",
        prefix: String = "",
        postfix: String = ""
): String {
    val result = StringBuilder(prefix)
    for((index, element) in this.withIndex()) {
        if (index > 0)
            result.append(separator)
        result.append(element)
    }
    result.append(postfix)
    return result.toString()
}

open class View () {
    open fun click() = println("View clicked")
}

class Button: View() {
    override fun click() = println("Button CLicked")
}

fun View.showOff() = println("view show off")
fun Button.showOff() = println("Button show off")