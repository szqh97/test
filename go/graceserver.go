package main

import (
	"context"
	"errors"
	"flag"
	"github.com/julienschmidt/httprouter"
	"log"
	"net"
	"net/http"
	"os"
	"os/exec"
	"os/signal"
	"syscall"
	"time"
)

var (
	server   *http.Server
	listener net.Listener
	graceful = flag.Bool("graceful", false, "listen on fd open 3 (internal use only)")
	router   = httprouter.New()
)

func handler(w http.ResponseWriter, r *http.Request, _ httprouter.Params) {
	//time.Sleep(time.Duration(20) * time.Second)
	w.Write([]byte("hello world "))
	//http.ListenAndServe(":9999", handler)
}

func reload() error {
	tl, ok := listener.(*net.TCPListener)
	if !ok {
		return errors.New("listener is not tcp listener")
	}

	f, err := tl.File()
	if err != nil {
		return err
	}

	args := []string{"-graceful"}
	cmd := exec.Command(os.Args[0], args...)
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr

	cmd.ExtraFiles = []*os.File{f}
	return cmd.Start()
}

func signalHandler() {
	ch := make(chan os.Signal, 1)
	signal.Notify(ch, syscall.SIGINT, syscall.SIGTERM, syscall.SIGUSR2)

	for {
		sig := <-ch
		log.Printf("signal: %v", sig)

		// timeout context for shutdown
		ctx, _ := context.WithTimeout(context.Background(), 20*time.Second)
		switch sig {
		case syscall.SIGINT, syscall.SIGTERM:
			// stop
			log.Println("stop")
			signal.Stop(ch)
			server.Shutdown(ctx)
			log.Println("graceful shutdown")
			return
		case syscall.SIGUSR2:
			//reload
			log.Println("reload")
			err := reload()
			if err != nil {
				log.Fatalf("graceful restart error: %v", err)
			}
			server.Shutdown(ctx)
			log.Println("graceful reload")
			return

		}
	}
}

func main() {
	flag.Parse()
	router.GET("/hello", handler)
	server = &http.Server{Addr: ":9999", Handler: router}

	f, _ := os.Open("/tmp/t.go")
	log.Println(f)

	var err error
	if *graceful {
		log.Println("main: Listening to existing file descriptor 3.")

		f := os.NewFile(3, "")
		if f == nil {
			log.Fatalf("new File on descriptor 3 failed")
		}
		listener, err = net.FileListener(f)

	} else {
		log.Println("main: Listening on a new file descriptor.")
		listener, err = net.Listen("tcp", server.Addr)
	}

	if err != nil {
		log.Fatalf("Listener error: %v", err)
	}

	go func() {
		err = server.Serve(listener)
		log.Printf("server.Serve err: %v\n", err)
	}()
	signalHandler()
	log.Println("signal end")
}
