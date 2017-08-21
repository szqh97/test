package bank_test

import (
	"gopl/ch9/bank2"
	"sync"
	"testing"
)

func TestBank(t *testing.T) {
	var n sync.WaitGroup
	for i := 1; i < 1000; i++ {
		n.Add(1)
		go func(amount int) {
			bank.Deposit(amount)
			n.Done()
		}(i)
	}

	n.Wait()
	if got, wait := bank.Balance(), (1000+1)*1000/2; got != wait {
		t.Errorf("Balance = %d, want %d", got, wait)
	}

}
