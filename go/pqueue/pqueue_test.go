package pqueue

import (
	"container/heap"
	"math/rand"
	"sort"
	"testing"
    "log"

	"github.com/bmizerany/assert"
)

func TestPriorityQueue(t *testing.T) {
	c := 100
	pq := New(c)

	for i := 0; i < c+1; i++ {
		heap.Push(&pq, &Item{Value: 2*i, Priority: int64(i+1000)})
	}

	for i := 0; i < c+1; i++ {
		item := heap.Pop(&pq)
	}
	assert.Equal(t, cap(pq), c/4)
}

func TestUnsortedInsert(t *testing.T) {
	c := 100
	pq := New(c)
	ints := make([]int, 0, c)

	for i := 0; i < c; i++ {
		v := rand.Int()
		ints = append(ints, v)
		heap.Push(&pq, &Item{Value: i, Priority: int64(v)})
	}
	assert.Equal(t, pq.Len(), c)
	assert.Equal(t, cap(pq), c)

	sort.Sort(sort.IntSlice(ints))

	for i := 0; i < c; i++ {
		item, _ := pq.PeekAndShift(int64(ints[len(ints)-1]))
		assert.Equal(t, item.Priority, int64(ints[i]))
	}
}

func TestRemove(t *testing.T) {
	c := 100
	pq := New(c)

	for i := 0; i < c; i++ {
		v := rand.Int()
		heap.Push(&pq, &Item{Value: "test", Priority: int64(v)})
	}

	for i := 0; i < 10; i++ {
		heap.Remove(&pq, rand.Intn((c-1)-i))
	}

	lastPriority := heap.Pop(&pq).(*Item).Priority
	for i := 0; i < (c - 10 - 1); i++ {
		item := heap.Pop(&pq)
		assert.Equal(t, lastPriority < item.(*Item).Priority, true)
		lastPriority = item.(*Item).Priority
	}
}
