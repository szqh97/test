package main

import "fmt"

func main() {
	months := [...]string{
		1:  "January",
		2:  "February",
		3:  "March",
		4:  "April",
		5:  "May",
		6:  "Jue",
		7:  "July",
		8:  "August",
		9:  "September",
		10: "October",
		11: "November",
		12: "December",
	}
	Q2 := months[4:7]
	summer := months[6:9]
	fmt.Println(Q2)
	fmt.Println(summer)

	for _, s := range Q2 {
		for _, q := range summer {
			if s == q {
				fmt.Println(s)

			}
		}
	}

}
