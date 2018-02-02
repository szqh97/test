package main

import (
	"fmt"
	"io/ioutil"
	"net/http"
)

const (
	g_url string = "http://www.baidu.com"
)

func RequestFuture(url string) <-chan []byte {
	c := make(chan []byte, 1)
	go func() {
		var body []byte
		defer func() {
			c <- body
		}()

		resp, err := http.Get(url)
		if err != nil {
			return
		}
		defer resp.Body.Close()
		body, _ = ioutil.ReadAll(resp.Body)
	}()
	return c

}

func RequestFuture2(url string) func() ([]byte, error) {
	var body []byte
	var err error

	c := make(chan struct{}, 1)
	go func() {
		defer close(c)

		var res *http.Response
		res, err = http.Get(url)
		if err != nil {
			return
		}

		defer res.Body.Close()
		body, err = ioutil.ReadAll(res.Body)
	}()

	return func() ([]byte, error) {
		<-c
		return body, err
	}

}

func GetURL(url string) ([]byte, error) {
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return nil, err
	}
	return body, err

}

func Future(f func() (interface{}, error)) func() (interface{}, error) {
	var result interface{}
	var err error

	c := make(chan struct{}, 1)
	go func() {
		defer close(c)
		result, err = f()
	}()

	return func() (interface{}, error) {
		<-c
		return result, err
	}
}

func GetURLWrap() (interface{}, error) {
	return GetURL(g_url)
}
func main() {
	fmt.Println("vim-go")
	future := RequestFuture("https://api.github.com/users/octocat/orgs")
	body := <-future
	fmt.Printf("response length: %d", len(body))

	futureV2 := RequestFuture2("https://api.github.com/users/octocat/orgs")
	bodyv2, _ := futureV2()
	fmt.Println("-------")

	fmt.Println(string(bodyv2))

	url := "https://api.github.com/users/octocat/orgs"

	future3 := Future(func() (interface{}, error) {
		resp, err := http.Get(url)
		if err != nil {
			return nil, err
		}
		defer resp.Body.Close()
		return ioutil.ReadAll(resp.Body)
	})
	future3 = Future(GetURLWrap)
	b, _ := future3()
	body, _ = b.([]byte)
	fmt.Println(string(body))

}
