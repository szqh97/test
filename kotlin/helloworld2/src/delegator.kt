/**
 * Created by szqh97 on 17-5-26.
 */

package delegator
import kotlin.properties.Delegates

interface  Base {
    fun print()
}

class BaseImpl(val x: Int) : Base {
    override fun print(){print(x)}
}

class Derived(b: Base) : Base by b


val lazVal: String by lazy {
    println("computed!")
    "Hello"
}

class UUser {
    var name: String by Delegates.observable("<no name>") {
        prop, old, new ->
        println("$old->$new")
    }
}

class MUser(val map: Map<String, Any?>) {
    val name: String by map
    val age: Int by map
}

