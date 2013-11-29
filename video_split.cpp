#include "video_split.h"
#include <iomanip>
#define DEBUG 1            /*  */

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

int video_split_processor::init()
{
    m_cfg.hist_th = 0.5;
    m_cfg.diff_cnt_th = 5;
    m_cfg.var_th = 100.0;

    //mp_sd = new shot_detector((uint32_t)p_info->width, (uint32_t)p_info->height, \
    //       4, 4, m_cfg);
#if DEBUG
    if (mp_sd)
    {
        cout << "mp_sd is NULL" << endl;
    }
    else
    {
        cout << "mp_sd_ is OK" << endl;
    }
#endif

    memset(&m_prev_end_time, 0, sizeof(live_timeval));
    memset(&m_shot_end_time, 0, sizeof(live_timeval));
    memset(&m_shot_begin_time, 0, sizeof(live_timeval));
    m_tmp_video = new char[FILE_NAME_LEN];
    m_video_file = new char[FILE_NAME_LEN];
#if DEBUG 
    cout << "initial ok!" << endl;
#endif
    
    return 0;
}

video_split_processor::~video_split_processor()
{
    rename_yuv_file();
#if DEBUG
    cout << "destructor" << endl;
    cout << m_video_file << endl;
#endif
    
    if (mp_sd) delete mp_sd;
    if (m_tmp_video) delete m_tmp_video;
    if (m_video_file) delete m_video_file;
    if (m_fp) 
    {
        fclose(m_fp);
        m_fp = NULL;
    }
}


int video_split_processor::rename_yuv_file()
{
#if 0
    sprintf(m_video_file, "%s/%lld%03lld.%lld%03lld.yuv", m_video_path, \
            m_shot_begin_time.tv_sec, m_shot_begin_time.tv_usec / 1000,
            m_shot_end_time.tv_sec, m_shot_end_time.tv_usec / 1000 );
    int ret = rename(m_tmp_video, m_video_file);
    return ret;
#endif
}

int video_split_processor::write_shot_info()
{
    char shot_info_file[FILE_NAME_LEN];
    sprintf(shot_info_file, "%s/%lld%03lld.%lld%03lld.yuv", m_shot_info_path, \
            m_shot_begin_time.tv_sec, m_shot_begin_time.tv_usec / 1000,
            m_shot_end_time.tv_sec, m_shot_end_time.tv_usec / 1000 );
    FILE *fp = fopen(shot_info_file, "w");
    
    fclose(fp);
    fp = NULL;

}

// TODO wirite shot boundary info to files
// 1. deal m_curr_frame_ts
// 2. timediff of two video file is large
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
    if (!mb_initialized)
    {
        // 1. init video_split_processor
        // 2. create a new yuv file
        memcpy(&m_shot_begin_time, &p_info->begin_time, sizeof(live_timeval));
        mp_sd = new shot_detector((uint32_t)p_info->width, \
                (uint32_t)p_info->height, 4, 4, m_cfg);
        memset(m_tmp_video, 0, FILE_NAME_LEN);
        sprintf(m_tmp_video, "%s/tmp_%lld%03lld.yuv", m_video_path, \
                p_info->begin_time.tv_sec, p_info->begin_time.tv_usec / 1000 );
        m_fp = fopen(m_tmp_video, "w+");
        
        mp_sd->restart(frame_buf, fts);
        size_t s = fwrite(frame_buf, len, 1, m_fp);
        m_curr_frame_ts = fts;

        memcpy(&m_shot_begin_time, &p_info->begin_time, sizeof(live_timeval));
        mb_initialized = true;
#if DEBUG
        cout << "wirte size "<< s << endl;
        cout << "begintime" << m_shot_begin_time.tv_sec << "." << m_shot_begin_time.tv_usec << endl;
#endif 
    }
    else
    {
        // TODO
        // 1. detect shot
        // 2. write frame to yuv file
        // 3. frame offset

        m_curr_shot = mp_sd->detect(frame_buf, m_curr_frame_ts);
        fwrite(frame_buf, len, 1, m_fp);
        if (m_curr_shot.start > 0 and m_curr_shot.end > 0)
        {
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }

            memcpy(&m_shot_end_time, &p_info->begin_time, sizeof(live_timeval));
            rename_yuv_file();

            timeval tv;
            unsigned int t_seconds = (p_info->begin_time.tv_usec + fts) / 1000;
            tv.tv_usec = (p_info->begin_time.tv_usec + fts) % 1000;
            tv.tv_sec = p_info->begin_time.tv_sec + t_seconds;

            m_shot_begin_time.tv_sec = tv.tv_sec;
            m_shot_begin_time.tv_usec = tv.tv_usec;
            memset(m_tmp_video, 0, FILE_NAME_LEN);
            sprintf(m_tmp_video, "%s/tmp_%lld%03lld.yuv", m_video_path, \
                    p_info->begin_time.tv_sec, p_info->begin_time.tv_usec / 1000 );
            m_fp = fopen(m_tmp_video, "w");
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
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }

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

            memset(m_tmp_video, 0, FILE_NAME_LEN);
            sprintf(m_tmp_video, "%s/tmp_%ld%ld.yuv", m_video_path, \
                    tv.tv_sec, tv.tv_usec / 1000);
            m_fp = fopen(m_tmp_video, "w");

        }
    }
    
#if 0
    // last frame and first frame in diff viedeo files
    if (timevaldiff(m_prev_end_time, p_info->begin_time) > 1000)
    {
        // 1. close old yuv video file 
        // 2. create a new yuv video file 
        // 3. restart shotdetector
        // 4. reset m_frame_count
        if (m_fp)
        {
            fclose(m_fp);
            m_fp = NULL;
        }
        sprintf(m_tmp_video, "%s/tmp_%lld%lld.yuv", m_video_path, \
                p_info->begin_time.tv_sec, p_info->begin_time.tv_usec / 1000 );
        
        //rename
        m_fp = fopen(m_tmp_video, "w+");

        //TODO restart
        //mp_sd->restart();
        
    }
#endif
    memcpy(&m_prev_end_time, &(p_info->end_time), sizeof(live_timeval));
    // if the last video_file to deal
    memcpy(&m_shot_end_time, &(p_info->end_time), sizeof(live_timeval));

    return 0;
}



int main ( int argc, char *argv[] )
{

    const char *video_path = ".";
    video_split_processor v(video_path);
    v.init();
    for (int i = 1; i < argc ; ++i)
    {
        char *video_file_name = argv[i];
        //const char *video_file_name = "20131129_053145.336953.video";
        // for test
        struct timeval t1, t2;
        FILE *fp = fopen(video_file_name, "r");
        if (!fp)
        {
            cerr << "Open file " << video_file_name << " fails" << endl;
            return -1;
        }
        size_t offset = sizeof(video_file_info);
        cout  << "offset is " << offset << endl;
        int ret = fseek(fp, -offset, SEEK_END);

        if (ret)
        {
            cerr << "fseek fails" << endl;
            fclose(fp);
            return -1;
        }

        off_t pos = ftello(fp);
        video_file_info info;
        ret = fread(&info, offset, 1, fp);
        if (ret != 1)
        {
            cerr << "Read file fails" << endl;
            fclose(fp);
            return -1;
        }
        cout << "position : " << pos << " width : " << info.width 
            << " height: " << info.height << " frame rate : " << info.frame_rate 
            << " frame_count : " << info.frame_count << " begin_time : " 
            << info.begin_time.tv_sec << "." << info.begin_time.tv_usec 
            << " end_time : " << info.end_time.tv_sec << "." 
            << info.end_time.tv_usec << endl;

        v.video_split(fp, pos, &info);
    }

    return 0;
}			/* ----------  end of function main  ---------- */
