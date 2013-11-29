#include "video_split.h"

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
long int timevaldiff(const live_timeval &start_time, \
        const live_timeval &end_time)
{
    long int msec;
    msec = (end_time.tv_sec - start_time.tv_sec) * 1000;
    msec += (end_time.tv_usec - start_time.tv_usec) / 1000;
    return msec;
}

video_split_processor::video_split_processor(const char *video_path):
    m_prev_shot(-1, -1, 0, 0, 0, BOUNDARY, BOUNDARY, -1), 
    m_curr_shot(-1, -1, 0, 0, 0, BOUNDARY, BOUNDARY, -1)
{

    mb_initialized = false;
    mp_sd = NULL;
    m_fp = NULL;
    m_video_path = ".";
    m_curr_frame_ts = 0;
}

int video_split_processor::init(video_file_info *p_info)
{
    mb_initialized = true;
    m_cfg.hist_th = 0.5;
    m_cfg.diff_cnt_th = 5;
    m_cfg.var_th = 100.0;

    mp_sd = new shot_detector((uint32_t)p_info->width, (uint32_t)p_info->height, \
            4, 4, m_cfg);

    memset(&m_prev_end_time, 0, sizeof(live_timeval));
    m_tmp_video = new char[FILE_NAME_LEN];
    m_video_file = new char[FILE_NAME_LEN];
    
    return 0;
}

video_split_processor::~video_split_processor()
{
    if (mb_initialized)
    {
        if (mp_sd) delete mp_sd;
        if (m_tmp_video) delete m_tmp_video;
        if (m_video_file) delete m_video_file;
    }
}


int video_split_processor::rename_yuv_file()
{
    sprintf(m_video_file, "%s/%lld%lld.%lld%lld.yuv", m_video_path, \
            m_shot_begin_time.tv_sec, m_shot_begin_time.tv_usec / 1000,
            m_shot_end_time.tv_sec, m_shot_end_time.tv_usec / 1000 );
    int ret = rename(m_tmp_video, m_video_file);
    return ret;
}

int video_split_processor::write_shot_info()
{
    char shot_info_file[FILE_NAME_LEN];
    sprintf(shot_info_file, "%s/%lld%lld.%lld%lld.yuv", m_shot_info_path, \
            m_shot_begin_time.tv_sec, m_shot_begin_time.tv_usec / 1000,
            m_shot_end_time.tv_sec, m_shot_end_time.tv_usec / 1000 );
    FILE *fp = fopen(shot_info_file, "w");
    
    fclose(fp);

}

// TODO wirite shot boundary info to files
// 1. deal m_curr_frame_ts
int video_split_processor::video_split(FILE *fp, off_t pos, video_file_info *p_info)
{

    off_t len = p_info->width * p_info->height * 2;
    int fts = 1000 / p_info->frame_rate;
    size_t mapped_size = 0;
    unsigned char *mapped_buffer = map_file(fp, len * (int)p_info->frame_count, \
            mapped_size);
    unsigned char frame_buf[len];
    memset(frame_buf, 0, len);
    memcpy(frame_buf, mapped_buffer, len);
    m_curr_frame_ts += fts;

    // first time detect invoke restart after init
    if (mb_initialized)
    {
        // 1. init video_split_processor
        // 2. create a new yuv file
        init(p_info);

        sprintf(m_tmp_video, "%s/tmp_%lld%lld.yuv", m_video_path, \
                p_info->begin_time.tv_sec, p_info->begin_time.tv_usec / 1000 );
        m_fp = fopen(m_tmp_video, "w+");
        
        mp_sd->restart(frame_buf, fts);
        fwrite(frame_buf, len, 1, m_fp);
        m_curr_frame_ts = fts;

        memcpy(&m_shot_begin_time, &p_info->begin_time, sizeof(live_timeval));
    }
    else
    {
        // TODO
        // 1. detect shot
        // 2. write frame to yuv file
        // 3. frame offset

        m_curr_shot = mp_sd->detect(frame_buf, m_curr_frame_ts);
        if (m_curr_shot.start > 0 and m_curr_shot.end > 0)
        {
            fwrite(frame_buf, len, 1, m_fp);
            fclose(m_fp);

            memcpy(&m_shot_end_time, &p_info->begin_time, sizeof(live_timeval));
            rename_yuv_file();

            timeval tv;
            unsigned int t_seconds = (p_info->begin_time.tv_usec + fts) / 1000;
            tv.tv_usec = (p_info->begin_time.tv_usec + fts) % 1000;
            tv.tv_sec = p_info->begin_time.tv_sec + t_seconds;

            sprintf(m_tmp_video, "%s/tmp_%lld%lld.yuv", m_video_path, \
                    p_info->begin_time.tv_sec, p_info->begin_time.tv_usec / 1000 );
            m_fp = fopen(m_tmp_video, "w");
        }
        else
        {
            fwrite(frame_buf, len, 1, m_fp);
        }
    }

    for(int i = 1; i < p_info->frame_count; ++i)
    {
        memcpy(frame_buf, mapped_buffer + i * len, len);
        m_curr_frame_ts += fts;
        m_curr_shot = mp_sd->detect(frame_buf, m_curr_frame_ts);
        fwrite(frame_buf, len, 1, m_fp);

        if (m_curr_shot.start > 0 and m_curr_shot.end > 0)
        {
            m_prev_shot = m_curr_shot;
            fclose(m_fp);

            // current shot end time
            timeval tv; 
            unsigned int t_seconds = p_info->begin_time.tv_usec + (i * fts) / 1000;
            tv.tv_sec = p_info->begin_time.tv_sec + (i * fts) / 1000 + t_seconds;
            tv.tv_usec = p_info->begin_time.tv_usec + (i * fts) % 1000;
            m_shot_end_time.tv_sec = tv.tv_sec;
            m_shot_end_time.tv_usec = tv.tv_usec;

            rename_yuv_file();

            // next shot begin time
            tv.tv_usec = (tv.tv_usec + fts * 1000) % 1000;
            t_seconds = (tv.tv_usec + fts * 1000) / 1000;
            tv.tv_sec = tv.tv_sec + t_seconds;
            m_shot_begin_time.tv_sec = tv.tv_sec;
            m_shot_begin_time.tv_usec = tv.tv_usec;

            sprintf(m_tmp_video, "%s/tmp_%ld%ld.yuv", m_video_path, \
                    tv.tv_sec, tv.tv_usec / 1000);
            m_fp = fopen(m_tmp_video, "w");

        }
    }
    
    // last frame and first frame in diff viedeo files
    if (timevaldiff(m_prev_end_time, p_info->begin_time) > 1000)
    {
        // 1. close old yuv video file 
        // 2. create a new yuv video file 
        // 3. restart shotdetector
        // 4. reset m_frame_count
        fclose(m_fp);
        sprintf(m_tmp_video, "%s/tmp_%lld%lld.yuv", m_video_path, \
                p_info->begin_time.tv_sec, p_info->begin_time.tv_usec / 1000 );
        
        //rename
        m_fp = fopen(m_tmp_video, "w+");

        //TODO restart
        //mp_sd->restart();
        
    }
    memcpy(&m_prev_end_time, &(p_info->end_time), sizeof(live_timeval));

    return 0;
}


int main ( int argc, char *argv[] )
{
    const char *video_path = ".";
    video_split_processor v(video_path);

    return 0;
}			/* ----------  end of function main  ---------- */
