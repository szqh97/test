/**
 * Created by szqh97 on 17-6-4.
 */
package delegation
class DelegatingCollection<T> : Collection<T>{
    private val innerList = arrayListOf<T>()
    override val size: Int get() = innerList.size
    override fun isEmpty(): Boolean  = innerList.isEmpty()
    override fun contains(element: T): Boolean  = innerList.contains(element)
    override fun iterator(): Iterator<T> = innerList.iterator()
    override fun containsAll(elements: Collection<T>): Boolean  =
            innerList.containsAll(elements)
}
