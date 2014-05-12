#define _FILE_OFFSET_BITS 64
/// vfp.cpp:
/// Copyright (c) 2010 Vobile Inc.  All Rights Reserved.
/// Author: zongzhen zhang <zhang_zongzhen@vobile.cn>
/// Created 2010-06-24
#include <sys/mman.h>
#include <sys/time.h>
#include <unistd.h>
//#include <glog/logging.h>
#include <errno.h>
#include <sstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <iomanip>
using std::setfill;
using std::setw;
using std::cout;
using std::endl;
using std::stringstream;
#define TOSTRING(x) " " #x ": "
#define LOG(LEVEL) cout << endl << time(NULL) << TOSTRING(LEVEL)
#include "fileProcessor.h"
#include <capture/include/sig_capture.h>
#include <deinterlace/deinterlace.h>
#include <fingerprint/headers/vfp_wrap.h>
#include <idnagen_lib/include/idnagen.h>
#include <stdio.h>
#include <string.h>

const double idnas_fps = 2.0;
unsigned char *map_file(FILE * fp, size_t size, size_t & mapped_size);
extern bool edge_prune;
extern bool idna_enable;
extern bool screenshot_enable;
extern double screenshot_rate;

extern unsigned int width, height, block_w, block_h;

int FileProcessor::process_video_file(const char *dir, const char *file_name, uint32_t name_len)    /* name_len include '\0' */
{
    char name_buffer[FILE_NAME_LEN];
    sprintf(name_buffer, "%s/%s", dir, file_name);
    FILE *fp = fopen(name_buffer, "r");
    if (!fp)
    {
        LOG(ERROR) << "Open file " << name_buffer << " fails";
        return 0;
    }
    size_t offset = sizeof(video_file_info);
    int ret = fseek(fp, -offset, SEEK_END);
    if (ret)
    {
        LOG(ERROR) << "fseek fails: " << file_name ;
        fclose(fp);
        return 0;
    }
    off_t pos = ftello(fp);
    video_file_info info;
    ret = fread(&info, offset, 1, fp);
    if (ret != 1)
    {
        LOG(ERROR) << "Read file fails";
        fclose(fp);
        return 0;
    }
    LOG(INFO) << "position : " << pos << " width : " << info.width << " height: "
        << info.height << " frame rate : " << info.frame_rate << " frame_count : "
        << info.frame_count << " begin_time : " << info.begin_time.tv_sec << "." 
        << setfill('0') << setw(6)<< info.begin_time.tv_usec << " end_time : " 
        << info.end_time.tv_sec << "." << setfill('0') << setw(6) 
        << info.end_time.tv_usec << " program time : from " << 
        m_current_task_begin_time.tv_sec << " to " << m_current_task_end_time.tv_sec;
    if (info.width > 0 && info.height > 0 && info.frame_count > 0
            && (int64_t) info.begin_time.tv_sec > (m_current_time.tv_sec - 36000)
            && (int64_t) info.end_time.tv_sec < (m_current_time.tv_sec + 36000)
            && (int64_t) info.end_time.tv_sec >= (int64_t) info.begin_time.tv_sec
            && (long long)(info.frame_count * info.width * info.height * 2) == pos)
    {
        if (m_width == 0 && m_height == 0)
        {
            m_width = info.width;
            m_height = info.height;
        }
        else if (m_width != info.width || m_height != info.height)
        {
            fclose(fp);
            return -1;          // exit from here because of width or height changed.
        }
        if (edge_prune == true)
        {
            if ((m_width == 1920 && m_height == 1080) || (m_width == 1280 && m_height == 720))
            {
                // ok.
            }
            else
            {
                fclose(fp);
                return -1;      // exit from here because of no need of video prune.
            }
        }

    }
    else
    {
        LOG(ERROR) << "Bad file format.";
        fclose(fp);
        unlink(name_buffer);
        return 0;
    }

    generate_picture(fp, pos, &info);
    generate_vfp(fp, pos, &info);
    fclose(fp);
    unlink(name_buffer);


    return 0;
}

int FileProcessor::generate_picture(FILE * fp, off_t pos, video_file_info * info)
{
    if (edge_prune == true)
    {
        return 0;
    }
    time_t a, b;
    // suseconds_t c, d;
    a = m_last_picture_generation_time.tv_sec;
    b = m_current_time.tv_sec;
    // c = m_last_picture_generation_time.tv_usec;
    // d = m_current_time.tv_usec;
    if (b - a >= 3)
    {                           // one picture per second
        int ret = fseek(fp, 0, SEEK_SET);
        if (ret)
        {
            LOG(FATAL) << "fseek fails for generating picture";
        }
        off_t len = pos / info->frame_count;
        unsigned char buffer[len];
        ret = fread(buffer, len, 1, fp);
        if (ret == 1)
        {
            char name_buffer[FILE_NAME_LEN];
            sprintf(name_buffer, "%s.tmp", m_picture_path);
            //printf ("buffer:%p, witdh:%d, height:%d, name_buffer:%s, buff len:%d, buff last char: %d\n", buffer, info->width, info->height, name_buffer, (int)len, (int)buffer[len - 1]);
            //printf("pos: %d, frame count: %d\n", (int)pos, (int)info->frame_count);
            gen_jpg_file(buffer, info->width, info->height, info->width * 2, info->color_type,
                    name_buffer);
            //make_image_copy(name_buffer);
            rename(name_buffer, m_picture_path);
            m_last_picture_generation_time = m_current_time;
        }
        else
        {
            LOG(ERROR) << "Read file fails";
        }
    }

    return 0;
}

int FileProcessor::generate_picture(char *buffer, int width, int height, const char *filename,
        int color_type)
{
    gen_jpg_file((unsigned char *)buffer, width, height, width * 2, color_type,
            (char *)filename);
    return 0;
}

int file_copy(const char *from, const char *to)
{
    FILE *fp1 = fopen(from, "r");
    FILE *fp2 = fopen(to, "w");
    char buffer[4096];
    while (!feof(fp1) && fp1 && fp2)
    {
        int count = fread(buffer, 1, sizeof(buffer), fp1);
        if (count > 0)
        {
            fwrite(buffer, count, 1, fp2);
        }
    }
    if (fp1)
    {
        fclose(fp1);
    }
    if (fp2)
    {
        fclose(fp2);
    }
    return 0;
}

int FileProcessor::make_image_copy(const char *file_name)
{
    if (m_cfp_file
            && time(NULL) >= (long long int)m_current_task_begin_time.tv_sec + m_image_time)
    {
        if (m_image_time_series.empty())
        {
            m_image_time = time(NULL);
        }
        else
        {
            m_image_time = m_image_time_series.front();
            m_image_time_series.pop_front();
        }
        char buffer[1024];
        char image_path[1024];
        sprintf(image_path, "%s/%lld.jpg", m_dna_path, (long long int)m_current_task_id);
        sprintf(buffer, "%s/%lld.%lld.jpg", m_dna_path, (long long int)m_current_task_id,
                (long long int)time(NULL));
        file_copy(file_name, buffer);
        rename(buffer, image_path);
    }
    return 0;
}

STATE FileProcessor::get_state(video_file_info * info)
{
    //  task.begin_time <= video.begin_time <= task.end_time

    long long t1, t2, v1, v2;
    t1 = m_current_task_begin_time.tv_sec;
    t2 = m_current_task_end_time.tv_sec;
    v1 = v2 = m_current_time.tv_sec;

    // t......t...v.....v (t>0)
    if (0 < t1 && t2 <= v1)
    {
        return FINISHED;
    }
    // t......t...v.....v or v....v....t......t
    if (t2 <= v1 || v2 < t1)
    {
        return OUT_DOOR;
    }

    // v .... t....t ......v
    if (v1 <= t1 && t2 <= v2)
    {
        return TRAVERSE;
    }

    // v... t....v.....t
    if (v1 <= t1 && t1 <= v2 && v2 <= t2)
    {
        return COMING_IN;
    }

    // t.....v.......v...........t
    if (t1 <= v1 && v2 <= t2)
    {
        return IN;
    }

    // t.....v......t........v
    if (t1 <= v1 && v1 <= t2 && t2 <= v2)
    {
        return GOING_OUT;
    }
    LOG(FATAL) << "Can not go here.";
    return OUT_DOOR;
}

int FileProcessor::generate_vfp(FILE * fp, off_t pos, video_file_info * info)
{

    STATE state = get_state(info);
    switch (state)
    {
        case OUT_DOOR:
            break;
        case FINISHED:
            goto_init_state();
            update_task_time();
            generate_vfp(fp, pos, info);
            break;
        case COMING_IN:
        case IN:
        case GOING_OUT:
        case TRAVERSE:
            fingerprint_vfp(fp, pos, info);
            break;
        default:
            LOG(FATAL) << "Can not go here.";
            break;
    }

    return 0;
}

int FileProcessor::init_cfp_handler(FILE * fp, off_t pos, video_file_info * info)
{
    if (info->frame_count > 1)
    {
        long long diff_time = info->end_time.tv_sec - info->begin_time.tv_sec;
        diff_time *= 1000000;
        diff_time += info->end_time.tv_usec - info->begin_time.tv_usec;
        int count = (info->frame_count - 1);
        if (info->frame_rate > 0)
        {
            fps = info->frame_rate;
        }
        else
        {
            fps = count * 1000000 / diff_time;
        }
        LOG(INFO) << "fps:" << fps;
    }
    m_vfp_wrap_context = vfp_open(info->width, info->height, info->width, fps, 0);
    if (!m_vfp_wrap_context)
    {
        LOG(FATAL) << "init vfp handle fails";
    }

    //cal frame time offset.
    {
        long long a, b, c, d;
        struct timeval tv;
        gettimeofday(&tv, NULL);
        a = tv.tv_sec;
        b = m_current_task_begin_time.tv_sec;
        c = tv.tv_usec;
        d = m_current_task_begin_time.tv_usec;
        frame_time_offset = (a - b) + (double)(c - d) / 1000000;
        first_frame_time_offset = - (1000 * info->frame_count / fps);
    }

    if (frame_time_offset <= 0)
    {
        frame_time_offset = 0;
    }
    LOG(INFO) << "frame_time_offset:" << frame_time_offset;

    if (edge_prune)
    {
        int ret = 0;
        if (m_width == 1920 && m_height == 1080)
        {
            ret = vfp_set_crop(m_vfp_wrap_context, 0, 0, 240, 240);

        }
        else if (m_width == 1280 && m_height == 720)
        {
            ret = vfp_set_crop(m_vfp_wrap_context, 0, 0, 160, 160);
        }
        if (ret)
        {
            LOG(FATAL) << "set crop for vfp handle fails";
        }
    }
    else
    {
        vfp_set_crop(m_vfp_wrap_context, 0, 0, 0, 0);
    }
    unsigned char buffer[48];
    int ret = vfp_get_header(m_vfp_wrap_context, buffer);
    if (ret)
    {
        LOG(FATAL) << "get vfp header fails.";
    }
    char dna_file[100];
    m_image_time_series.clear();
    long long int i = (m_current_task_end_time.tv_sec - m_current_task_begin_time.tv_sec);
    for (i /= 3; i > 0; i /= 3)
    {
        //m_image_time_series.push_front(i);
    }
    m_image_time = 0;
    const char *suffix;
    if (edge_prune == false)
    {
        suffix = "cdna";
    }
    else
    {
        suffix = "xdna";
    }
    sprintf(dna_file, "%s/%lld.%lld.%s", m_dna_path, (long long)m_channel_id,
            (long long int)info->begin_time.tv_sec, suffix);
    unlink(dna_file);
    m_cfp_file = fopen(dna_file, "w");
    if (!m_cfp_file)
    {
        LOG(ERROR) << "open file " << dna_file << " for write fails.";
        return 0;
    }
    if (m_current_task_pcm_enable || m_current_task_image_enable)
    {
        char data_file[FILE_NAME_LEN];
        struct timeval t1;
        gettimeofday(&t1, NULL);
        sprintf(data_file, "%s/%d_%ld_%ld.data", m_dna_path, m_channel_id, t1.tv_sec, t1.tv_usec);
        if (!m_cfp_file)
        {
            m_cfp_file = fopen(data_file, "w");
            if (m_cfp_file)
            {
                LOG(ERROR) << "open file " << data_file << " for write fails.";
            }
        }
    }
    dna_cb.serial_number = 0;
    write_dna_control_block(VIDEO_DNA, sizeof(buffer), info->begin_time.tv_sec * 1000 + info->begin_time.tv_usec / 1000, m_cfp_file);
    //write_dna_control_block(VIDEO_DNA, sizeof(buffer), m_current_task_begin_time.tv_sec * 1000 + first_frame_time_offset, m_cfp_file);
    fwrite(buffer, sizeof(buffer), 1, m_cfp_file);
    fflush(m_cfp_file);

    m_frame_count = 0;
    edge_info_t edge_info = { {0}
    };
    edge_info.width = info->width;
    edge_info.height = info->height;
    edge_info.length = 0;
    ret = vdna_init_edge_detect(&m_detect, &edge_info, DETECT_DYNAMIC);
    if (ret)
    {
        LOG(FATAL) << "init edge detect fails.";
    }
    return 0;
}

void FileProcessor::pack_snapshot_file(long long timestamp)
{
    FILE *fp = fopen(m_snapshot_file_path, "r");
    if (!fp)
        return;
    struct stat st;
    int ret;
    ret = fstat(fileno(fp), &st);
    if (ret)
    {
        fclose(fp);
        return;
    }
    off_t file_size = st.st_size;
    char *buffer = (char *)malloc(file_size);
    if (!buffer)
    {
        fclose(fp);
        return;
    }
    int c = fread(buffer, file_size, 1, fp);
    if (c == 1)
    {
        write_dna_control_block(SNAPSHOT, file_size, timestamp + first_frame_time_offset, m_cfp_file);
        fwrite(buffer, file_size, 1, m_cfp_file);
        fflush(m_cfp_file);
    }

    free(buffer);
    fclose(fp);
    return;
}

int FileProcessor::fingerprint_vfp(FILE * fp, off_t pos, video_file_info * info)
{

    if (!m_vfp_wrap_context)
    {
        int ret = init_cfp_handler(fp, pos, info);
        if (ret)
        {
            LOG(FATAL) << "init vfp handler fails.";
        }
    }
    int ret = fseek(fp, 0, SEEK_SET);
    if (ret)
    {
        LOG(ERROR) << "fseek fails for generating vfp";
    }
    int i;
    off_t len = pos / info->frame_count;
    unsigned char *buffer0 = NULL;
    unsigned char *buffer = NULL;
    unsigned char *buffer_pointer = NULL;
    unsigned char vdna_body[100];
    size_t mapped_size = 0;
    unsigned char *mapped_buffer = map_file(fp, len * (int)info->frame_count, mapped_size);
    if (!mapped_buffer)
    {
        buffer0 = (unsigned char *)malloc(len);
        buffer = (unsigned char *)malloc(len);
        buffer_pointer = buffer;
    }

    if (!m_vdna_buffer)
    {
        m_vdna_buffer = new vdna_buffer;
        m_vdna_buffer->buf = new unsigned char[info->frame_count * 40];
        m_vdna_buffer->cur = m_vdna_buffer->buf;
        m_vdna_buffer->vdna_buf_len = info->frame_count * 40;
    }

    for (i = 0; i < (int)info->frame_count; i++)
    {
        if (mapped_buffer)
        {
            buffer_pointer = mapped_buffer + (i * len);
        }
        else
        {
            int read_count = fread(buffer, len, 1, fp);
            if (read_count == 1)
            {
                if ((m_current_live_query_setting || idna_enable)
                        && i == ((int)info->frame_count - 2))
                {
                    memcpy(buffer0, buffer, len);
                }
            }
            else
            {
                LOG(ERROR) << "read file fails.";
                ret = -1;
                break;
            }
        }

        float frame_ts = (m_frame_count + 1) / fps;

        int count =
            vfp_process_frame(buffer_pointer, info->width, info->height, info->width * 2,
                    info->color_type,
                     frame_ts, m_vfp_wrap_context,
                     vdna_body,
                    m_detect, &m_edge);
        if (count != 40)
        {
            LOG(ERROR) << "call vfp_process_frame fails, fps: " << frame_time_offset + m_frame_count / fps << " info->color_type: " << info->color_type << " info->width: " << info->width << " info->height: " << info->height << " frame_time_offset: " << frame_time_offset << " m_frame_count:"  << m_frame_count  << " fps: "  << fps ;
        }
        else 
        {
            if (m_vdna_time_offset == -1)
            {
                unsigned int dna_ts = (unsigned int)vdna_body;
                m_vdna_time_offset = m_current_task_begin_time.tv_sec * 1000 + m_current_task_begin_time.tv_usec / 1000 + frame_ts - dna_ts;
                LOG(INFO) << "vdna delay: "<< m_vdna_time_offset ;
            }
            //if (m_vdna_buffer->cur + count <= m_vdna_buffer->buf + m_vdna_buffer->vdna_buf_len)
            if (m_vdna_buffer->cur_len + count <= m_vdna_buffer->vdna_buf_len)
            {
                memcpy(m_vdna_buffer->cur, vdna_body, count);
                m_vdna_buffer->cur += count;
                m_vdna_buffer->cur_len += count;
            }
            else
            {
                unsigned int dna_ts = (unsigned int) m_vdna_buffer->buf;
                write_dna_control_block(VIDEO_DNA, info->frame_count * 40, \
                    m_vdna_time_offset + dna_ts, m_cfp_file);
                    //info->begin_time.tv_sec * 1000 + info->begin_time.tv_usec / 1000 - m_vdna_time_offset, m_cfp_file);
                fwrite(m_vdna_buffer->buf, m_vdna_buffer->cur_len, 1, m_cfp_file);
                fflush(m_cfp_file);
                m_vdna_buffer->buf = m_vdna_buffer->cur;
                m_vdna_buffer->cur_len = 0;
            }

        }

        // video split to get shot info
        video_split(fp, buffer_pointer, (double)frame_ts * 1000, m_channel_id,\
                info, m_current_task_begin_time, m_current_task_end_time);

        m_frame_count++;
    }

    if (mapped_buffer)
    {
        munmap(mapped_buffer, mapped_size);
    }
    if (buffer0)
    {
        free(buffer0);
        buffer0 = NULL;
    }
    if (buffer)
    {
        free(buffer);
        buffer = NULL;
    }

    return 0;
}

#if 0
unsigned char *map_file(FILE * fp, size_t size, size_t & mapped_size)
{
    int fd = fileno(fp);
    int page_size = sysconf(_SC_PAGE_SIZE);
    int aligned_size = (size + page_size - 1) / page_size * page_size;

    unsigned char *addr = (unsigned char *)mmap(NULL, aligned_size, PROT_READ,
            MAP_PRIVATE, fd, 0);
    if (addr == (unsigned char *)(-1))
    {
        return NULL;
    }
    else
    {
    }
    mapped_size = aligned_size;
    return addr;
}
#endif

int FileProcessor::idna_gen_deinterlace(char *&idna_buf, size_t & idna_buf_size,
        const char *frame0, const char *frame1,
        const size_t frame_size, const char *fname,
        const unsigned width, const unsigned height,
        const unsigned stride, const int color_type,
        const unsigned frame_serial_no,
        const unsigned long frame_time_at,
        const unsigned limited_size)
{
    int y_size = width * height;
    char *buffer0;
    char *buffer1;
    char *buffer2;
    posix_memalign((void **)&buffer0, 64, y_size);
    posix_memalign((void **)&buffer1, 64, y_size);
    posix_memalign((void **)&buffer2, 64, y_size);

    int i;
    if (color_type == CAPTURE_PIX_FMT_UYVY)
    {
        for (i = 0; i < y_size; i++)
        {
            buffer0[i] = frame0[i * 2 + 1];
            buffer1[i] = frame1[i * 2 + 1];
        }
    }
    else
    {
        for (i = 0; i < y_size; i++)
        {
            buffer0[i] = frame0[i * 2];
            buffer1[i] = frame1[i * 2];
        }
    }

#ifdef DEBUG
    struct timeval tv1, tv2, tv3;
    gettimeofday(&tv1, NULL);
#endif
    CDeinterlacer::Deinterlace((unsigned char *)buffer2, (unsigned char *)buffer1,
            (unsigned char *)buffer0, width, height);
#ifdef DEBUG
    gettimeofday(&tv2, NULL);
    long tc = (tv2.tv_sec - tv1.tv_sec) * 1000 + (tv2.tv_usec - tv1.tv_usec + 500) / 1000;
    LOG(INFO) << "calling Deinterlace consumes millisecond: " << tc;
#endif

    int ret = idna_gen(idna_buf, idna_buf_size, buffer2, y_size, fname, width, height, width, 0,
            frame_serial_no, frame_time_at, 16);
    generate_picture((char *)frame1, width, height, m_snapshot_file_path, color_type);
#ifdef DEBUG
    gettimeofday(&tv3, NULL);
    long ic = (tv3.tv_sec - tv2.tv_sec) * 1000 + (tv3.tv_usec - tv2.tv_usec + 500) / 1000;
    LOG(INFO) << "calling idna gen consumes millisecond: " << ic;
#endif

#ifdef DEBUG
    static int sn = 1;
    char *newframe;
    posix_memalign((void **)&newframe, 64, frame_size);
    int j = frame_size >> 2;
    if (color_type == CAPTURE_PIX_FMT_UYVY)
    {
        for (i = 0; i < j; i++)
        {
            newframe[4 * i + 0] = frame1[4 * i + 0];
            newframe[4 * i + 1] = buffer2[2 * i];
            newframe[4 * i + 2] = frame1[4 * i + 2];
            newframe[4 * i + 3] = buffer2[2 * i + 1];
        }
    }
    else
    {
        for (i = 0; i < j; i++)
        {
            newframe[4 * i + 0] = buffer2[2 * i];
            newframe[4 * i + 1] = frame1[4 * i + 1];
            newframe[4 * i + 2] = buffer2[2 * i + 1];
            newframe[4 * i + 3] = frame1[4 * i + 3];
        }

    }
    char name_buffer[300];
    sprintf(name_buffer, "%s", m_picture_path);
    char *p = strrchr(name_buffer, '/') + 1;
    sprintf(p, "%da.jpg", sn);
    generate_picture((char *)frame1, width, height, name_buffer, color_type);
    sprintf(p, "%db.jpg", sn);
    generate_picture((char *)newframe, width, height, name_buffer, color_type);
    sn++;
    free(newframe);

#endif

    free(buffer0);
    free(buffer1);
    free(buffer2);
    return ret;
}

int FileProcessor::generate_image_data(unsigned char *buffer, const struct video_file_info *info, int idna_len)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    if (idna_len >= 1000)
    {

        /*
         * the begin_time and end_time of struct image_info is the idle duration time.
         */
        if (live_time_cmp(m_curr_image_idle_info.begin_time, tv) <= 0 && live_time_cmp(tv, m_curr_image_idle_info.end_time) < 0)
        {
            // in the idle duration
        }
        else
        {

            LOG(INFO) << "image generating after idna generated.";
            char temp_filename[FILE_NAME_LEN];
            sprintf(temp_filename, "/tmp/tmp_%ld.jpg", tv.tv_sec);

            gen_jpg_file(buffer, info->width, info->height, info->width * 2, info->color_type, temp_filename);
            FILE *fp = fopen(temp_filename, "r");
            int ret;
            struct stat st;
            ret = fstat(fileno(fp), &st);
            if (ret)
            {
                fclose(fp);
                return -1;
            }
            off_t file_size = st.st_size;

            m_curr_image_idle_info.buffer = (char*) malloc(file_size);
            if (m_curr_image_idle_info.buffer == NULL)
            {
                LOG(ERROR) << "malloc memory failed" ;
                return -1;
            }
            memset(m_curr_image_idle_info.buffer, 0, file_size);
            m_curr_image_idle_info.buflen = file_size;
            fread(m_curr_image_idle_info.buffer, file_size, 1, fp);
            fclose(fp);
            unlink(temp_filename);

            struct data_file_info finfo;
            memset(&finfo, 0, sizeof(finfo));
            finfo.data_type = IMAGE_DATA;
            finfo.size = file_size;
            memcpy(&finfo.begin_time, &tv, sizeof(struct timeval));
            memcpy(&finfo.end_time, &tv, sizeof(struct timeval));

#if DATA_TEST
            char image_data_file[FILE_NAME_LEN];
            sprintf(image_data_file, "%s/%d_%ld_%ld.data", m_dna_path, m_channel_id, tv.tv_sec, tv.tv_usec);
            FILE *fout = fopen(image_data_file, "w");

            fwrite(&finfo, sizeof(finfo), 1, fout);
            fflush(fout);

            fwrite(m_curr_image_idle_info.buffer, file_size, 1, fout);
            fflush(fout);

            fclose(fout);
#endif

            fwrite(&finfo, sizeof(finfo), 1, m_data_file);
            fflush(m_data_file);


            fwrite(m_curr_image_idle_info.buffer, file_size, 1, m_data_file);
            fflush(m_data_file);

            m_curr_image_idle_info.begin_time.tv_sec = tv.tv_sec;
            m_curr_image_idle_info.begin_time.tv_usec = tv.tv_usec;
            long usec = tv.tv_usec + m_current_task_image_idle_duration % 1000 * 1000;
            m_curr_image_idle_info.end_time.tv_usec = usec % 1000000;
            m_curr_image_idle_info.end_time.tv_sec = tv.tv_sec + m_current_task_image_idle_duration / 1000 + usec / 1000000;

            LOG(INFO) << "m_curr_image_idle_info begintime " << m_curr_image_idle_info.begin_time.tv_sec << "." << m_curr_image_idle_info.begin_time.tv_usec << ", end time " << m_curr_image_idle_info.end_time.tv_sec << "." << m_curr_image_idle_info.end_time.tv_usec << "; current time " << tv.tv_sec << "." << tv.tv_usec ;

            if (m_curr_image_idle_info.buffer != NULL)
            {
                free(m_curr_image_idle_info.buffer);
                m_curr_image_idle_info.buffer = NULL;
            }
        }
    }
    return 0;
}

int FileProcessor::fingerprint_flush()
{
    int count = 0;
    unsigned char body[140];
    while( (count = vfp_flush_frame(m_vfp_wrap_context, body)))
    {
        if (count)
        {
            if(m_vdna_buffer->cur_len + count <= m_vdna_buffer->vdna_buf_len)
            {
                memcpy(m_vdna_buffer->cur, body, count);
                m_vdna_buffer->cur_len += count;
                m_vdna_buffer->cur += count;
            }
            else
            {
                unsigned int dna_ts = (unsigned int) m_vdna_buffer->buf;
                write_dna_control_block(VIDEO_DNA, m_vdna_buffer->cur_len, dna_ts + m_vdna_time_offset, m_cfp_file);
                fwrite(m_vdna_buffer->buf, m_vdna_buffer->cur_len, 1, m_cfp_file);
                fflush(m_cfp_file);
                m_vdna_buffer->cur = m_vdna_buffer->buf;
                m_vdna_buffer->cur_len = 0;

            }

        }
    }

    if (m_vdna_buffer->cur_len )
    {
        unsigned int dna_ts = (unsigned int) m_vdna_buffer->buf;
        write_dna_control_block(VIDEO_DNA, m_vdna_buffer->cur_len, dna_ts + m_vdna_time_offset, m_cfp_file);
        fwrite(m_vdna_buffer->buf, m_vdna_buffer->cur_len, 1, m_cfp_file);
        fflush(m_cfp_file);
        m_vdna_buffer->cur = m_vdna_buffer->buf;
        m_vdna_buffer->cur_len = 0;

    }
    return 0;
}

