package main
iimport (
    "fmt"
)
type Any interface{}
type EvalFunc func(Any)(Any, Any)

func main() {
    evenFunc := func(state Any) (Any, Any) {
        os := state.(int)
        ns := os + 2
        return os, ns
    }
    even := BuildLazyIntEvaluator(evenFunc, 0)
    for i := 0; i < 10; i++ {
        fmt.Printf("%vth even: %v\n", i, even())
    }

}
func BuildlazyEvaluator(evalFunc EvalFunc, initSate Any) Func() Any{
    retValChan := make(chan Any)
    loopFunc := func() {
        var actState Any = initSate
        var retVal Any
        for {
            retVal, actState = evalFunc(actState)
            retValChan <- retVal
        }
    }
    retFunc := func() Any {
        return <- retValChan
    }
    go loopFunc()
    return retFunc
}

func BuildLazyIntEvaluator(evalFunc EvalFunc, initSate Any) func() int {
    ef := BuildLazyIntEvaluator(evalFunc, initSate)
    return func() int {
        return ef().(int)
    }
}
