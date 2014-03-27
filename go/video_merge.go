package main

import (
	"errors"
	"fsnotify"
	"log"
	"os/exec"
	"strings"
)

type av_list map[string]string

func (avl *av_list) process_in_moved_to(file string) error {
	var (
		f_a, f_v   string
		outf       string
		channel_id string
	)
	splitedfile := strings.Split(file, ".")
	if len(splitedfile) == 5 {
		channel_id = splitedfile[0]
	} else {
		log.Printf("file %s is error", file)
		return errors.New("file name error")
	}
	if f, ok := (*avl)[channel_id]; ok {
		delete(*avl, channel_id)

		if string(splitedfile[3]) == "a" {
			f_a = file
			f_v = f
			outf = strings.Join(strings.Split(f, ".")[0:3], ".") + ".mp4"
		} else if string(splitedfile[3]) == "v" {
			f_v = file
			f_a = f
			outf = strings.Join(strings.Split(f, ".")[0:3], ".") + ".mp4"
		}
		log.Println(f_v, f_a, outf)

		// merge video and audio
		cmd := exec.Command("ffmpeg", "-y", "-i", f_v, "-i", f_a, "-codec", "copy", outf) //, " >/dev/null 2>&1 ")
		//cmd := exec.Command("ffmpeg", " -y -i ", f_v, "-i ", f_a, " -codec copy ", outf, " >/dev/null 2>&1 ")
		//cmd := exec.Command("sleep", "5")
		err := cmd.Run()
		if err != nil {
			log.Fatal("ffmpeg merge", err)
			return err
		}
		cmd = exec.Command("rm", "-f", f_v, " ", f_a)
		err = cmd.Run()
		if err != nil {
			log.Fatal("rm files", err)
			return err
		}
	} else {
		(*avl)[channel_id] = file
	}
	return nil
}

func main() {
	monitorpath := "/home/li_yun/Projects/test/go"
	watcher, err := fsnotify.NewWatcher()
	if err != nil {
		log.Fatal(err)
	}

	done := make(chan bool)

	// Process events
	go func() {
		avfile_list := make(av_list)
		for {
			select {
			case ev := <-watcher.Event:
				(&avfile_list).process_in_moved_to(ev.Name)
			case err := <-watcher.Error:
				log.Println("error:", err)
			}
		}
	}()

	// only monitor FSN_RENAME event
	err = watcher.WatchFlags(monitorpath, fsnotify.FSN_MOVEDTO)
	//err = watcher.Watch(".")
	if err != nil {
		log.Fatal(err)
	}

	<-done

	/* ... do stuff ... */
	watcher.Close()
}
