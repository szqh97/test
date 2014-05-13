#define _FILE_OFFSET_BITS 64
/// fileProcessor.cpp:
/// Copyright (c) 2010 Vobile Inc.  All Rights Reserved.
/// Author: zongzhen zhang <zhang_zongzhen@vobile.cn>
/// Created 2010-06-24
#include <sys/time.h>
//#include <glog/logging.h>
#include <errno.h>
#include <iostream>
#include <strings.h>
using std::cout;
using std::endl;
#define TOSTRING(x) " " #x ": "
#define LOG(LEVEL) cout << endl << time(NULL) << TOSTRING(LEVEL)
#include "fileProcessor.h"
#include <capture/include/sig_capture.h>
#include <fingerprint/headers/vfp_wrap.h>
#include <stdio.h>

#ifdef PCM_DEBUG
extern FILE *pcm_file;
#endif

#ifdef NEW_AUDIO_DNA
#define AFP_CLOSE afp4_close
#else
#define AFP_CLOSE afp_close
#endif 

extern bool edge_prune;
const size_t MEDIA_FILE_NAME_LENGTH = sizeof("20090712_091032.521086.video");
const size_t avt_index = sizeof("20090712_091032.521086.v") - 1 - 1;    // 'v' index, from 0.

FileProcessor::FileProcessor(int channelid, const char *work_dir, const char *picture_path,
                             const char *dna_path, const char *snapshot_file_path, const char *video_path):
    video_split_processor(channelid, video_path, dna_path) 
{
    m_channel_id = channelid;
    bzero(&m_last_picture_generation_time, sizeof(m_last_picture_generation_time));

    gettimeofday(&m_current_time, NULL);
    bzero(&m_last_time, sizeof(m_last_time));
    gettimeofday(&m_new_time, NULL);

    bzero(&m_current_task_begin_time, sizeof(m_current_task_begin_time));
    bzero(&m_current_task_end_time, sizeof(m_current_task_end_time));
    m_current_task_id = 0;
    m_current_live_query_setting = false;
    m_next_live_query_setting = false;

    m_vfp_wrap_context = NULL;
    m_afp_wrap_context = NULL;
    fps = DEFAULT_FPS;
    m_audio_rate = 48000;

    bzero(&m_next_task_begin_time, sizeof(m_next_task_begin_time));
    bzero(&m_next_task_end_time, sizeof(m_next_task_end_time));
    m_next_task_id = 0;


    first_frame_time_offset = 0;
    first_pcm_time_offset = 0;

    m_work_dir = work_dir;
    m_picture_path = picture_path;
    m_dna_path = dna_path;
    m_cfp_file = NULL;
    dna_cb.serial_number = 0;
    m_detect = NULL;
    m_width = 0;
    m_height = 0;
    bzero(&m_edge, sizeof(m_edge));
    m_image_time = 0;
    m_snapshot_file_path = "/dev/null";
    if (snapshot_file_path)
    {
        m_snapshot_file_path = snapshot_file_path;
    }

    bzero(&m_curr_pcm_idle_info, sizeof(m_curr_pcm_idle_info));
    mb_pcm_start = true;
    bzero(&m_curr_image_idle_info, sizeof(m_curr_image_idle_info));
    m_data_file = NULL;
    m_prev_pcm_clip_duration = m_current_task_pcm_clip_duration = 0;

    m_vdna_time_offset = -1;
    m_vdna_buffer = NULL;

}

FileProcessor::~FileProcessor()
{
    if (m_curr_pcm_idle_info.buffer != NULL)
    {
        free(m_curr_pcm_idle_info.buffer);
        m_curr_pcm_idle_info.buffer = m_curr_pcm_idle_info.buffer_cur = m_curr_pcm_idle_info.buffer_end = NULL;
        m_curr_pcm_idle_info.buflen = m_curr_pcm_idle_info.byte_counter = 0;
    }
}

int FileProcessor::process_file(const char *dir, const char *file_name, uint32_t name_len)  /* name_len include '\0' */
{
    gettimeofday(&m_current_time, NULL);
    int ret = 0;
    if (name_len >= MEDIA_FILE_NAME_LENGTH)
    {                           // name_len including '\0'
        char ch = file_name[avt_index];
        if (ch == 'v')
        {
            ret = process_video_file(dir, file_name, name_len);
        }
        else if (ch == 'a')
        {
            if (edge_prune == false)
                ret = process_audio_file(dir, file_name, name_len);
        }
        else if (ch == 't')
        {
            ret = process_task_file(dir, file_name, name_len);
        }
        else
        {
            LOG(INFO) << "found some other file: " << file_name;
        }
    }
    else
    {
        LOG(INFO) << "found some other file: " << file_name;
    }
    return ret;
}

int FileProcessor::process_task_file(const char *dir, const char *file_name, uint32_t name_len) /* name_len include '\0' */
{
    char name_buffer[FILE_NAME_LEN];
    sprintf(name_buffer, "%s/%s", dir, file_name);
    FILE *fp = fopen(name_buffer, "r");
    if (!fp)
    {
        return 0;
    }
    long long int id, b1, b2, e1, e2, q;
    int pcm_enable, image_enable, pcm_channel, pcm_rate;
    long long int pcm_clip, pcm_idle, image_idle;

    int ret = 0;
    do {
        id = b1 = b2 = e1 = e2 = q = 0;
        pcm_enable = image_enable = pcm_channel = pcm_rate = 0;
        pcm_clip = pcm_idle = image_idle = 0;
        ret = fscanf(fp, "%lld %lld %lld %lld %d %lld %d %lld %d %d %lld", &id, &b1, &e1, &q, &pcm_enable, &pcm_clip, &pcm_rate, &pcm_idle,  &pcm_channel, &image_enable, &image_idle);
    } while ( ret == 11 && id >= 0 && e1 <= m_current_time.tv_sec);

    LOG(INFO) << "ret : " << ret << " EOF : " << EOF << " m_current_task_id : " <<
        m_current_task_id;
    if ((ret == EOF || ret == 11) && m_current_task_id != 0 && m_current_task_id != id)
    {
        LOG(INFO) << "goto init state.";
        goto_init_state();
    }

    if (ret == EOF || ret == 11)
    {
        LOG(INFO) << "update task info.";
        m_current_task_id = id;
        m_current_task_begin_time.tv_sec = b1;
        m_current_task_begin_time.tv_usec = b2;
        m_current_task_end_time.tv_sec = e1;
        m_current_task_end_time.tv_usec = e2;
        m_current_live_query_setting = (q == 1);
        m_current_task_pcm_enable = (pcm_enable == 1);
        m_current_task_image_enable = (image_enable == 1);
        m_current_task_pcm_channels = pcm_channel;
        m_current_task_pcm_rate = pcm_rate;
        m_current_task_pcm_clip_duration = pcm_clip;
        m_current_task_pcm_idle_duration = pcm_idle;
        m_current_task_image_idle_duration = image_idle;
        if (b1 > m_current_time.tv_sec)
        {
            goto_init_state();
        }
    }

    id = b1 = b2 = e1 = e2 = q = 0;
    pcm_enable = image_enable = pcm_channel = pcm_rate = 0;
    pcm_clip = pcm_idle = image_idle = 0;
    ret = fscanf(fp, "%lld %lld %lld %lld %d %lld %d %lld %d %d %lld", &id, &b1, &e1, &q, &pcm_enable, &pcm_clip, &pcm_rate, &pcm_idle, &pcm_channel, &image_enable, &image_idle);

    if (ret == EOF || ret == 11)
    {
        LOG(INFO) << "update next task info.";
        m_next_task_id = id;
        m_next_task_begin_time.tv_sec = b1;
        m_next_task_begin_time.tv_usec = b2;
        m_next_task_end_time.tv_sec = e1;
        m_next_task_end_time.tv_usec = e2;
        m_next_live_query_setting = (q == 1);
        m_next_task_pcm_enable = (pcm_enable == 1);
        m_next_task_image_enable = (image_enable == 1);
        m_next_task_pcm_channels = pcm_channel;
        m_next_task_pcm_rate = pcm_rate;
        m_next_task_pcm_clip_duration = pcm_clip;
        m_next_task_pcm_idle_duration = pcm_idle;
        m_next_task_image_idle_duration = image_idle;
    }

    fclose(fp);
    if (m_current_task_id == -1)
    {
        LOG(INFO) << "quit...";
        return -1;
    }
    return 0;
}

int FileProcessor::write_dna_control_block(int dna_type, int length, long long timestamp, FILE * out)
{
    dna_cb.type = dna_type;
    dna_cb.length = length;
    dna_cb.serial_number++;
    dna_cb.pad = 0;
    dna_cb.timestamp = timestamp;
    fwrite(&dna_cb, sizeof(dna_cb), 1, out);
    if (length == 0)
    {
        dna_cb.serial_number = 0;
    }
    return 0;
}

int FileProcessor::goto_init_state()
{
    LOG(INFO) << " close cfp file " << endl;
    if (m_cfp_file)
    {
        fingerprint_flush();
        write_dna_control_block(NONE_DNA, 0, 0, m_cfp_file);
        fclose(m_cfp_file);
        m_cfp_file = NULL;
        if (m_data_file)
        {
            fclose(m_data_file);
            m_data_file = NULL;
        }
    }

    if (m_vfp_wrap_context)
    {
        vfp_close(&m_vfp_wrap_context);
        m_vfp_wrap_context = NULL;
    }
    if (m_afp_wrap_context)
    {
        flush_afp();
        AFP_CLOSE(&m_afp_wrap_context);
        LOG(INFO) << "fingerprint finished.";
        m_afp_wrap_context = NULL;
    }
#ifdef PCM_DEBUG
    if (pcm_file)
    {
        fclose(pcm_file);
        pcm_file = NULL;
    }
#endif
    if (m_detect)
    {
        vdna_free_edge_detect(m_detect);
        m_detect = NULL;
    }
    finish_split();

    if (m_vdna_buffer)
    {
        //delete [] m_vdna_buffer->buf;
        free(m_vdna_buffer->buf);
        m_vdna_buffer->vdna_buf_len = 0;
        m_vdna_buffer->cur_len = 0;
        //delete m_vdna_buffer;
        free(m_vdna_buffer);
        m_vdna_buffer = NULL;
    }
    
    return 0;
}

int FileProcessor::update_task_time()
{

    m_current_task_begin_time = m_next_task_begin_time;
    m_current_task_end_time = m_next_task_end_time;
    m_current_task_id = m_next_task_id;
    m_current_live_query_setting = m_next_live_query_setting;
    m_current_task_pcm_enable = m_next_task_pcm_enable;
    m_current_task_pcm_rate = m_next_task_pcm_rate;
    m_current_task_pcm_channels = m_next_task_pcm_channels;
    m_current_task_pcm_clip_duration = m_next_task_pcm_clip_duration;
    m_current_task_pcm_idle_duration = m_next_task_pcm_idle_duration;
    m_current_task_image_enable = m_next_task_image_enable;
    m_current_task_image_idle_duration = m_next_task_pcm_idle_duration;

    bzero(&m_next_task_begin_time, sizeof(m_next_task_begin_time));
    bzero(&m_next_task_end_time, sizeof(m_next_task_end_time));
    m_next_task_id = 0;
    return 0;
}

