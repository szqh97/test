package main

import (
	"crypto/md5"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"strings"
)

func checkerr(err interface{}) {
	if err != nil {
		log.Fatal(err)
	}

}
func main() {
	if len(os.Args) < 2 {
		fmt.Printf("./%s username password\n", os.Args[0])
		os.Exit(1)
	}
	username := os.Args[1]
	password := os.Args[2]
	sign := "kp201408p" + password + "u" + username
	post_data := "u=" + username + "&p=" + password + "&sign="
	md5value := fmt.Sprintf("%x", md5.Sum([]byte(sign)))
	md5value = strings.ToUpper(md5value)
	post_data = post_data + md5value
	fmt.Println(md5value)
	fmt.Println(post_data)
	r := strings.NewReader(post_data)

	url := "http://192.169.1.11/v1/user/login"
	client := &http.Client{}
	request, err := http.NewRequest("POST", url, r)
	checkerr(err)
	request.Header.Add("Content-Type", "application/x-www-form-urlencoded")

	resp, err := client.Do(request)
	checkerr(err)

	defer resp.Body.Close()

	all, err := ioutil.ReadAll(resp.Body)
	checkerr(err)
	fmt.Printf("%s", all)

}
