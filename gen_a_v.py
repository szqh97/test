#!/usr/bin/python
# -*- coding: utf8 -*-

import datetime
import fcntl
import getopt
import os
import select
import struct
import subprocess
import sys
import threading
import time
import collections

# command options: -p 104857600 -d netStream3 -c mmst://livezf.wasu.cn/cctv5 -a None -o var/cache/raw_data/netStream3 -t both -r 1.0
G_COMMAND_OPTIONS = 'p:d:c:a:o:t:r:'
def parse_options():
    options = lambda : None
    options.ifps = 2.0
    try:
        opts, args = getopt.getopt(sys.argv[1:], G_COMMAND_OPTIONS)  # home path
    except getopt.GetoptError:
        print >> sys.stderr, "Use ffmpeg_process:data_buffer:c:a:o:t:r: as options"
        sys.exit(0)
        return None
    for o, a in opts:
        if o == "-c":
            options.url = a
        if o == '-o':
            options.path = a
        if o == '-r':
            options.ifps = float(a)

    return options

env = lambda : None
env.video_fifo = None
env.audio_fifo = None
env.vfps =25 
env.width = 0
env.height = 0
env.audio_rate = 0
env.options = parse_options()
env.last_come_time = time.time()
env.options.url="test.asf"
env.options.path= "./tmp"

def main():
    try:
        os.system("rm -rf %s/*.audio %s/*.video" % ((env.options.path,) * 2))
        env.video_fifo = os.path.join(env.options.path, "video.fifo")
        env.audio_fifo = os.path.join(env.options.path, "audio.fifo")

        try:
            os.mkfifo(env.video_fifo)
        except Exception, e1:
            pass

        try:
            os.mkfifo(env.audio_fifo)
        except Exception, e2:
            pass
        os.system("fuser -k %s %s" % (env.video_fifo, env.audio_fifo))


    except Exception, err:
        print err

    v = Video_capturer()
    a = Audio_capturer()
    v.setDaemon(True)
    a.setDaemon(True)
    v.start()
    a.start()

    cmdline = ['ffmpeg', '-y', '-i', env.options.url, '-f', 'rawvideo', '-pix_fmt', 'uyvy422', env.video_fifo, '-ac', '2', '-f', 's16le', '-acodec', 'pcm_s16le', env.audio_fifo]

    ffmpeg_process = subprocess.Popen(cmdline, stdin=subprocess.PIPE, stdout=open(os.devnull, 'w'), stderr=subprocess.PIPE)



    debug_out = file("./ffmpeg.out", "w")
    debug_out.write(" ".join(cmdline))
    debug_out.write("\n")
    debug_out.flush()


    pipe_stderr = ffmpeg_process.stderr
    set_nonblock(pipe_stderr)
    data_buffer = ''
    start_time = time.time()
    while True:
        current_time = time.time()
        if data_buffer.find('Corrupt stream') > 0 or abs(start_time - current_time) >= 60:
            debug_out.write(data_buffer)
            debug_out.flush()
            ffmpeg_process.kill()
            sys.exit(-1)
        try:
            delta = pipe_stderr.read(1)
            data_buffer += delta
        except IOError, err:
            if err.errno == 11:
                time.sleep(1)
                continue

        if data_buffer.find('to stop') > 0:
            debug_out.write(data_buffer)
            debug_out.flush()
            s = data_buffer.split()
            for i in range(len(s)):
                if s[i].startswith('uyvy422'):
                    print "found uyvy422:", s[i + 1]
                    x, y = s[i + 1].strip(",").split('x')
                    print "found width, height:", int(x), int(y)
                    env.width = int(x)
                    env.height = int(y)
                if env.width > 0 and s[i].startswith('tbc'):
                    print "found tbc:", s[i - 1]
                    env.vfps = float(s[i - 1])
                if s[i].startswith('pcm_s16le,'):
                    print 'found pcm_s16le:' + s[i + 1]
                    env.audio_rate = int(s[i+1])
                    print 'the audio_rate is ' + str(env.audio_rate)

            break

    while True:
        data_buffer = ''
        try:
            infds, _, _ = select.select([pipe_stderr], [], [], 10) 
            if len(infds) > 0:
                data_buffer = pipe_stderr.read(512)
        except IOError, err:
            if err.errno == 11:
                date_buffer = ''
                time.sleep(1)

        if len(data_buffer) > 0:
            debug_out.write(data_buffer)
            debug_out.flush()
            data_buffer = ''
        else:
            if ffmpeg_process.poll() != None:
                sys.exit(0)
            if env.last_come_time < time.time() - 60:
                ffmpeg_process.kill()
                sys.exit(-1)

def set_nonblock(fileHandler):
    fd = fileHandler.fileno()
    fl = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, fl | os.O_NONBLOCK)

class Video_capturer(threading.Thread):

    def __init__(self):
        threading.Thread.__init__(self)

    def run(self):
        f = file(env.video_fifo, "r")
        data_buffer = ''

        fts = int(round(1000 / env.vfps))

        while True:
            data_buffer += f.read(1024)
            frame_count = int(round(env.vfps / env.options.ifps))
            package_size = env.width * env.height * 2 * frame_count
            if package_size > 0:
                break;
            else:
                time.sleep(0.1)
        size = len(data_buffer) // package_size 
        data_buffer = data_buffer[package_size * size:]
        begin_time = time.time()
        while True:
            data_buffer += f.read(package_size -len(data_buffer))
            end_time = begin_time + float(fts * frame_count/ 1000.0)
            if len(data_buffer) >= package_size:
                time_to = time.time()
                env.last_come_time = time_to
                t = datetime.datetime.utcfromtimestamp(begin_time)
                filename = '%4s%2s%2s_%2s%2s%2s.%6s.video' % (t.year, t.month, t.day, t.hour, t.minute, t.second, t.microsecond)
                filename = filename.replace(' ', '0')
                filename = os.path.join(env.options.path, filename)
                vf = file(filename, "w")
                vf.write(data_buffer[0:package_size])
                data_buffer = data_buffer[package_size:]
                color_type = 1
                s = struct.pack('2HI2Hd', env.width, env.height, package_size, frame_count, color_type, env.vfps)
                vf.write(s)
                #s = struct.pack('4Q', int(time_from), int((time_from - int(time_from)) * 1000000), int(time_to), int((time_to - int(time_to)) * 1000000)) 
                s = struct.pack('4Q', int(begin_time), int((begin_time % 1) * 1000000), int(end_time), int((end_time % 1) * 1000000))
                vf.write(s)
                vf.close()
                begin_time = end_time 
class Audio_capturer(threading.Thread):

    def __init__(self):
        threading.Thread.__init__(self)

    def run(self):
        f = file(env.audio_fifo, "r")
        data_buffer = ''
        while True:
            data_buffer += f.read(1024)
            frame_count = int(round(env.audio_rate / env.options.ifps))
            package_size = 4 * frame_count
            if package_size > 0:
                break
            else:
                time.sleep(0.1)

        size = len(data_buffer) // package_size 
        data_buffer = data_buffer[package_size * size:]
        time_from = time.time()
        while True:
            data_buffer += f.read(package_size -len(data_buffer))
            if len(data_buffer) >= package_size:
                time_to = time.time()
                env.last_come_time = time_to
                t = datetime.datetime.utcfromtimestamp(time_from)
                filename = '%4s%2s%2s_%2s%2s%2s.%6s.audio' % (t.year, t.month, t.day, t.hour, t.minute, t.second, t.microsecond)
                filename = filename.replace(' ', '0')
                filename = os.path.join(env.options.path, filename)
                af = file(filename, "w")

                af.write(data_buffer[0:package_size])
                data_buffer = data_buffer[package_size:]

                s = struct.pack('2HI', 16, 2, env.audio_rate)
                af.write(s)
                s = struct.pack('4Q', int(time_from), int((time_from - int(time_from)) * 1000000), int(time_to), int((time_to - int(time_to)) * 1000000)) 
                af.write(s)
                af.close()
                time_from = time_to


if __name__ == '__main__':
    main()
