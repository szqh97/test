package main

import (
	"fmt"
	"log"

	"github.com/sideshow/apns2"
	"github.com/sideshow/apns2/certificate"
)

func main() {

	cert, err := certificate.FromP12File("./dj_apns_dev.p12", "123456")
	if err != nil {
		log.Fatal("Cert Error:", err)
	}

	notification := &apns2.Notification{}
	notification.Topic = "com.sideshow.Apns2"
	notification.DeviceToken = "0b901c2dd4313f82ce1da7b9e6ce13bf6fa02c0de7d91744c99af0e36c89be6a"
	notification.Payload = []byte(`{"aps":{"alert":"Hello!"}}`) // See Payload section below

	client := apns2.NewClient(cert).Production()
	apns2.HTTPClientTimeout = 0
	res, err := client.Push(notification)

	if err != nil {
		log.Fatal("Error:", err)
	}

	fmt.Printf("%v %v %v\n", res.StatusCode, res.ApnsID, res.Reason)
}
