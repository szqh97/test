package main

import (
	"fmt"
	"sync"

	"github.com/go-redis/redis"
)

func connectPool(client *redis.Client) {
	wg := sync.WaitGroup{}
	wg.Add(10)

	for i := 0; i < 10; i++ {
		go func() {
			defer wg.Done()

			for j := 0; j < 100; j++ {
				client.Set(fmt.Sprintf("name%d", j), fmt.Sprintf("xys%d", j), 0).Err()
				client.Get(fmt.Sprintf("name%d", j)).Result()

			}

			fmt.Printf("PoolStats, TotalConns: %d, FreeConns: %d\n", client.PoolStats().TotalConns, client.PoolStats().FreeConns)

		}()

	}

	wg.Wait()

}

func main() {
	client := redis.NewClient(&redis.Options{
		Addr:     "120.26.137.224:26379",
		Password: "",
		DB:       0,
		PoolSize: 5,
	})

	val, err := client.Get("kakakak").Result()
	if err != nil {
		fmt.Println("xxxxx", err)
		if err.Error() == "redis: nil" {
			fmt.Println("kkdkkdkdkdk")
		}
	}
	fmt.Println(val)

	err = client.Set("qiyuk", "szqh97", 0).Err()
	if err != nil {
		fmt.Println("set errror :", err)

	}

}
