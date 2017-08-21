package bank_test

import (
	"fmt"
	"gopl/ch9/bank1"
	"testing"
)

func TestBank(t *testing.T) {
	done := make(chan struct{})
	go func() {
		bank.Deposi(200)
		fmt.Println("=", bank.Balance())
		done <- struct{}{}
	}()

	go func() {
		bank.Deposi(100)
		done <- struct{}{}
	}()
	<-done
	<-done

	if got, want := bank.Balance(), 200; got != want {
		t.Errorf("Balance = %d, want %d", got, want)
	}
}
