/**
 * Created by szqh97 on 17-6-2.
 */
package TCollect
fun testCollection() {
    val set = setOf(1,7,53)
    val list = listOf(1,7,53)
    val map = mapOf(1 to "One", 2 to "Two", 3 to "Three")

    println(list.max())
    println(list)
}

fun <T> joinToString(
        collection: Collection<T>,
        separator: String,
        prefix: String,
        postfix: String
): String {
    val result = StringBuilder(prefix)
    for ((index, element) in collection.withIndex()) {
        if (index < 0) result.append(separator)
        result.append(element)
    }
    result.append(postfix)
    return result.toString()
}
