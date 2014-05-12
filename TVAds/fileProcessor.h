/// fileProcessor.h:
/// Copyright (c) 2010 Vobile Inc.  All Rights Reserved.
/// Author: zongzhen zhang <zhang_zongzhen@vobile.cn>
/// Created 2010-06-24
#ifndef __FILE_PROCESSOR_H__
#define __FILE_PROCESSOR_H__
#ifdef NEW_AUDIO_DNA
#include "afp4_wrap.h"
#endif

#include <capture/include/sig_capture.h>
#include <deque>
#include <fingerprint/headers/afp_wrap.h>
#include <fingerprint/headers/vfp_wrap.h>
#include <sys/time.h>
#include "util.h"
#include "video_split.h"
using std::deque;

typedef enum
{ OUT_DOOR, COMING_IN, IN, GOING_OUT, TRAVERSE, FINISHED } STATE;

#define NONE_DNA  0
#define VIDEO_DNA 1
#define IMAGE_DNA 2
#define AUDIO_DNA 3
#define SNAPSHOT  4
#define PCM_DATA  5
#define IMAGE_DATA 6

struct vdna_buffer
{
    unsigned char *buf;
    unsigned char *cur;
    size_t cur_len;
    size_t vdna_buf_len;
};

class FileProcessor : public video_split_processor
{
  public:
    FileProcessor(int channelid, const char *work_dir, const char *picture_path,
                  const char *dna_path, const char *snapshot_file_path, const char *video_path);
                  //float hist_th, int diff_cn_th, float var_th, int min_len, int max_len);
    ~FileProcessor();
    int process_file(const char *dir, const char *file_name, uint32_t name_len);
    int process_video_file(const char *dir, const char *file_name, uint32_t name_len);
    int process_audio_file(const char *dir, const char *file_name, uint32_t name_len);
    int process_task_file(const char *dir, const char *file_name, uint32_t name_len);
    int generate_picture(FILE * fp, off_t pos, video_file_info * info);
    int generate_picture(char *buffer, int width, int height, const char *filename,
                         int color_type);
    int idna_gen_deinterlace(char *&idna_buf, size_t & idna_buf_size, const char *frame0,
                             const char *frame1, const size_t frame_size, const char *fname,
                             const unsigned width, const unsigned height, const unsigned stride,
                             const int color_type, const unsigned frame_serial_no,
                             const unsigned long frame_time_at, const unsigned limited_size);
    int generate_vfp(FILE * fp, off_t pos, video_file_info * info);
    int generate_afp(FILE * fp, off_t pos, audio_file_info * info);
    int fingerprint_vfp(FILE * fp, off_t pos, video_file_info * info);
    int fingerprint_flush();
    int fingerprint_afp(FILE * fp, off_t pos, audio_file_info * info);
    int init_cfp_handler(FILE * fp, off_t pos, video_file_info * info);
    int init_afp_handler(FILE * fp, off_t pos, audio_file_info * info);
    int write_dna_control_block(int dna_type, int length,long long timestamp, FILE * out);
    STATE get_state(video_file_info * info);
    int goto_init_state();
    int update_task_time();
    int flush_afp();
    int make_image_copy(const char *file_name);
    int generate_pcm_data(const unsigned char *buffer, const off_t len, const int count, const audio_file_info *info);
    int generate_image_data(unsigned char *buffer, const struct video_file_info *info, int idna_len);
    long long int m_image_time;
    deque < long long int >m_image_time_series;
  private:
    int m_channel_id;
    void pack_snapshot_file(long long timestamp);
    struct timeval m_last_picture_generation_time;
    struct timeval m_current_time;
    struct timeval m_new_time;
    struct timeval m_last_time;
    const char *m_picture_path;
    const char *m_dna_path;
    const char *m_snapshot_file_path;
    const char *m_work_dir;
    long long int m_current_task_id;
    live_timeval m_current_task_begin_time;
    live_timeval m_current_task_end_time;

    long long int m_next_task_id;
    live_timeval m_next_task_begin_time;
    live_timeval m_next_task_end_time;
    bool m_current_live_query_setting;
    bool m_next_live_query_setting;

    vfp_wrap_context *m_vfp_wrap_context;
#ifdef NEW_AUDIO_DNA
    afp4_wrap_context *m_afp_wrap_context;
#else
    afp_wrap_context *m_afp_wrap_context;
#endif
    FILE *m_cfp_file;
    struct dna_control_block
    {
        int serial_number;
        int type;
        int length;
        int pad;
        long long timestamp;    // millisecond.
    };
    dna_control_block dna_cb;
    vdna_edge_detect_t m_detect;
    vdna_edge_info_t m_edge;
    long long int m_frame_count;
    long long int m_audio_count;
    uint32_t m_audio_rate;
    int m_width;
    int m_height;
    double fps;
    double frame_time_offset;
    double pcm_time_offset;
    long long first_frame_time_offset;
    long long first_pcm_time_offset;

    bool m_current_task_pcm_enable;
    bool m_current_task_image_enable;
    int m_current_task_pcm_channels;
    int m_current_task_pcm_rate;
    unsigned long long m_current_task_pcm_clip_duration;
    unsigned long long m_current_task_pcm_idle_duration;
    unsigned long long m_current_task_image_idle_duration;
    bool m_next_task_pcm_enable;
    bool m_next_task_image_enable;
    int m_next_task_pcm_channels;
    int m_next_task_pcm_rate;
    unsigned long long m_prev_pcm_clip_duration;
    unsigned long long m_next_task_pcm_clip_duration;
    unsigned long long m_next_task_pcm_idle_duration;
    unsigned long long m_next_task_image_idle_duration;
    struct pcm_file_info m_curr_pcm_idle_info;
    struct timeval prev_pcm_endtime;
    struct imge_info m_curr_image_idle_info;

    bool mb_pcm_start ;
    FILE *m_data_file;

    long long m_vdna_time_offset;
    vdna_buffer *m_vdna_buffer;

};

//#define FILE_NAME_LEN 2048
extern const size_t MEDIA_FILE_NAME_LENGTH;
extern const size_t avt_index;

#endif
