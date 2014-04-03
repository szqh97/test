package main

import (
    "log"
    "os"
    "os/exec"
    "strings"
    "time"

    "pidlock"
    "logger"
    "fsnotify"
    "goconfig"
)

type av_list map[string]string

func install_logger() {
    logger.SetConsole(true)
    logger.SetRollingFile("./var/log", "video_merge.log", 20, 20, logger.MB)
    logger.SetRollingDaily("./var/log", "video_merge.log")
    logger.SetLevel(logger.DEBUG)
}

func getMonitorPath() (mpath string, err error) {
    cfg, err := goconfig.LoadConfigFile("./etc/live_box.conf")
    if err != nil {
        logger.Fatal("load config file live_box.conf failed!")
        return "", err
    }
    return cfg.GetValue("taskGenerator", "video_path")
}

func (avl *av_list) process_in_moved_to(file string) error {
    var (
        f_a, f_v   string
        outf       string
        channel_id string
    )

    // check the file name is like ./1.1111111.1111111.a.mp4
    splitedfile := strings.Split(file, ".")
    if len(splitedfile) == 5 {
        channel_id = splitedfile[0]
    } else {
        logger.Warn("file %s is error", file)
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
        logger.Info("f_v: " + f_v + ", f_a: " + f_a + ", outf: " + outf)

        time.Sleep(time.Duration(time.Second*5))
        // merge video and audio
        cmd := exec.Command("ffmpeg", "-y", "-i", f_v, "-i", f_a, "-codec", "copy", outf)
        //cmd := exec.Command("ffmpeg", " -y -i ", f_v, "-i ", f_a, " -codec copy ", outf, " >/dev/null 2>&1 ")
        logger.Info("cmd's args is: ", cmd.Args)
        err := cmd.Run()
        if err != nil {
            logger.Fatal("ffmpeg merge video error:", err)
        } else {
            cmd = exec.Command("rm", "-f", f_v, " ", f_a)
            err = cmd.Run()
            if err != nil {
                logger.Warn("rm files error: %s", err)
            }
        }
    } else {
        (*avl)[channel_id] = file
    }
    return nil
}

func main() {
    pid_file := "./var/run/taskgenerator.pid"
    pid_locker, err := pidlock.Lock_write_pid_file(pid_file)
    logger.Info("starting ...")
    install_logger()
    //monitorpath := "/home/li_yun/Projects/test/go"
    monitorpath, err := getMonitorPath()
    if err != nil {
        logger.Fatal("get monitor path error: %s", err)
        os.Exit(1)
    }
    log.Println(monitorpath)
    watcher, err := fsnotify.NewWatcher()
    if err != nil {
        logger.Fatal("newWatcher error: %s", err)
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
                logger.Warn("errror: %s", err)
            }
        }
    }()

    // only monitor FSN_RENAME event
    err = watcher.WatchFlags(monitorpath, fsnotify.FSN_MOVEDTO)
    if err != nil {
        logger.Fatal("add watch flags error: %s", err)
    }

    <-done
    /* ... do stuff ... */
    watcher.Close()
    pid_locker.Close()
    logger.Info("done ...")

}
