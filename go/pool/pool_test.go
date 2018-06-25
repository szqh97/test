package pool

import (
	"sync"
	"testing"
)

func GoPool2() {
	wg := new(sync.WaitGroup)
	data := make(chan int, 100)
	for i := 0; i < 10; i++ {
		wg.Add(i)
		go func(n int) {
			defer wg.Done()
			for _ = range data {
				//	fmt.Println("goroutine:", n, i)

			}
		}(i)
	}

	for i := 0; i < 10000; i++ {
		data <- i
	}
	close(data)
	//wg.Wait()

}
func NoPool2() {
	wg := new(sync.WaitGroup)
	for i := 0; i < 10000; i++ {
		wg.Add(1)
		go func(n int) {
			defer wg.Done()
			//		fmt.Println("goroutine", n)

		}(i)
	}

	wg.Wait()
}
func BenchmarkGopool(b *testing.B) {
	for i := 0; i < b.N; i++ {
		GoPool2()
	}
}

func BenchmarkNopool(b *testing.B) {
	for i := 0; i < b.N; i++ {
		NoPool2()
	}
}
