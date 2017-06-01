/**
 * Created by li_yun on 2017/5/31.
 */
package SmartCast

interface Expr
class Num(val value: Int) : Expr
class Sum(val left: Expr, val right: Expr): Expr

fun eval(e: Expr): Int {
    if (e is Num ) {
        val n = e as Num
        return n.value
    }
    if (e is Sum) {
        return eval(e.right) + eval(e.left)
    }
    throw  IllegalArgumentException("Unkonwn expresssion")
}

fun eval2(e: Expr): Int =
    when(e) {
        is Num -> e.value
        is Sum -> eval(e.right) + eval(e.left)
        else -> throw IllegalArgumentException("Unkonw expression")
    }

fun evalWithLoggin(e: Expr): Int =
    when(e) {
        is Num -> {
            println("num: ${e.value}")
            e.value
        }
        is Sum -> {
            val left = evalWithLoggin(e.left)
            val right = evalWithLoggin(e.right)
            println("sum: $left + $right")
            left + right
        }
        else -> throw  IllegalArgumentException("Unkown expression")
    }
