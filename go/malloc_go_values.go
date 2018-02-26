package main

import (
	"fmt"
)

const (
	_PageSize    = 1 << 13
	GoosWindows  = 0
	GoarchArm64  = 0
	GoosDarwin   = 1
	GoarchMips   = 0
	GoarchMipsle = 0
	_PageShift   = 13
	PtrSize      = 4 << (^uintptr(0) >> 63)
)

func round(n, a uintptr) uintptr {
	return (n + a - 1) &^ (a - 1)
}

func main() {
	_64bit := 1 << (^uintptr(0) >> 63) / 2
	fmt.Printf("_64bit = %d\n", _64bit)
	var _MHeapMap_TotalBits uint = uint((_64bit*GoosWindows)*35 + (_64bit*(1-GoosWindows)*(1-GoosDarwin*GoarchArm64))*39 + GoosDarwin*GoarchArm64*31 + (1-_64bit)*(32-(GoarchMips+GoarchMipsle)))
	fmt.Printf("_MHeapMap_TotalBits = %d\n", _MHeapMap_TotalBits)
	var _MHeapMap_Bits uint = _MHeapMap_TotalBits - _PageShift
	fmt.Printf("_MHeapMap_Bits = %d\n", _MHeapMap_Bits)

	_MaxMem := uintptr(1<<_MHeapMap_TotalBits - 1)

	fmt.Printf("_MaxMem = %d\n", _MaxMem)
	var bitmapSize uintptr = (_MaxMem + 1) / (PtrSize * 8 / 2)
	fmt.Printf("bitmapSize = %d\n", bitmapSize)
	arenaSize := round(_MaxMem, 1<<13)
	fmt.Printf("arenaSize = %d\n", arenaSize)
	var spansSize uintptr = (_MaxMem + 1) / _PageSize * PtrSize
	fmt.Printf("spansSize = %d\n", spansSize)

}
