#ifndef _VIDEO_SPLIT_H_
#define _VIDEO_SPLIT_H_
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <stdint.h>
#include <cstdio>
#include <vector>

#include "shot_detector.hpp"
#define FILE_NAME_LEN 2048

using namespace std;

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

class video_split_processor
{
    public:
        video_split_processor(const char *video_path);
        ~video_split_processor();
        int video_split(FILE *fp, off_t pos, video_file_info *p_info);
        int init();
    private:
        bool mb_initialized;
        const char *m_video_path;
        char *m_tmp_video;
        char *m_video_file;
        const char *m_vdna_path;
        const char *m_vdna_name;
        const char *m_shot_info_path;
        config m_cfg;
        shot_detector *mp_sd;
        shot m_prev_shot;
        shot m_curr_shot;
        FILE *m_fp;
        live_timeval m_prev_end_time;

        live_timeval m_shot_begin_time;
        live_timeval m_shot_end_time;

        unsigned int m_curr_frame_ts;
        
        video_file_info m_prev_info;

        int rename_yuv_file();
        int write_shot_info();
    
};


#endif
