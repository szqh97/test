/**
 * Created by li_yun on 2017/6/2.
 */
package strings

import java.io.Serializable

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

var StringBuilder.lastChar: Char
    get() = get(length - 1)
    set(value: Char) {
        this.setCharAt(length - 1 , value)
    }

interface Clickable {
    fun click()
    fun showOff() = println("I'm clickable")
}


open class RichButton : Clickable {
    final override fun click() {}
}

interface State : Serializable



class Outer {
    inner  class Inner {
        fun getOuterReference(): Outer = this@Outer
    }
}

class User constructor(_nickname: String) {
    val nickname: String
    init {
        nickname = _nickname
    }
}


