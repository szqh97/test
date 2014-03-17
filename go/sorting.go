package sort

type Interface interface {
    Len() int
    Less(i, j int) bool
    Swap(i, j int)
}

type IntArray []int

func (p IntArray) Len() int {return len(p)}
func (p IntArray) Less(i, j int)bool {return p[i] < p[j]}
func (p IntArray) Swap(i,j int)     {p[i], p[j] = p[j], p[i]}
func Sort (data Interface) {
    for i := 1; i < data.Len(); i++ {
        for j := i; j > 0 && data.Less(j, j-1); j-- {
            data.Swap(j , j-1)
        }
    }
}


