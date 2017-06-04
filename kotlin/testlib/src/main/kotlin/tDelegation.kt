/**
 * Created by szqh97 on 17-6-4.
 */
package delegation

import com.sun.org.apache.xpath.internal.operations.Bool

/*
class DelegatingCollection<T> : Collection<T>{
    private val innerList = arrayListOf<T>()
    override val size: Int get() = innerList.size
    override fun isEmpty(): Boolean  = innerList.isEmpty()
    override fun contains(element: T): Boolean  = innerList.contains(element)
    override fun iterator(): Iterator<T> = innerList.iterator()
    override fun containsAll(elements: Collection<T>): Boolean  =
            innerList.containsAll(elements)
}
*/

class DelegatingCollection<T>(
        innerList: Collection<T> = ArrayList<T>()
) : Collection<T> by innerList {}

class CountingSet<T>(
        val innerSet: MutableCollection<T> = HashSet<T>()
) : MutableCollection<T> by innerSet {
    var objectAdded = 0
    override fun add(element: T): Boolean {
        objectAdded ++
        return innerSet.add(element)
    }
    override fun addAll (c: Collection<T>): Boolean {
        objectAdded += c.size
        return innerSet.addAll(c)
        }
}
