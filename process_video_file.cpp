/*
 * process_video_file.cpp
 *  Author: Li Yun <li_yun@163.com>
 */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <stdint.h>
#include <cstdio>

#include "shot_detector.hpp"
using namespace std;
unsigned char *map_file(FILE * fp, size_t size, size_t & mapped_size);

struct live_timeval
{
    uint64_t tv_sec;
    uint64_t tv_usec;
};

struct audio_file_info
{
    uint16_t bit;
    uint16_t channel;
    uint32_t rate;

    struct live_timeval begin_time;
    struct live_timeval end_time;
};

struct video_file_info
{
    uint16_t width;
    uint16_t height;
    uint32_t image_size;
    uint16_t frame_count;
    uint16_t color_type;
    double frame_rate;

    struct live_timeval begin_time;
    struct live_timeval end_time;
};

int split_video(FILE *fp, off_t pos, video_file_info *info)
{


}
