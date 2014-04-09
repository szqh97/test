package main
import (
    "fmt"
)

type Any interface {}
type EvalFunc func(Any) (Any, Any)
