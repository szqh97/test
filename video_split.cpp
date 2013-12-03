#include "video_split.h"
#include <unistd.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#define DEBUG 1                  

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
void get_Y(uint16_t color_type, unsigned char *frame, unsigned char *y_buffer, int y_size)
{

    if (color_type == CAPTURE_PIX_FMT_UYVY)
    {
        for (int i = 0; i < y_size; i++)
        {
            y_buffer[i] = frame[i * 2 + 1];
        }
    }
    else
    {
        for (int i = 0; i < y_size; i++)
        {
            y_buffer[i] = frame[i * 2];
        }
    }

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
    m_fshot = NULL;
    m_video_path = ".";
    m_curr_frame_ts = 0;
}

int video_split_processor::init()
{
    m_cfg.hist_th = 0.5;
    m_cfg.diff_cnt_th = 5;
    m_cfg.var_th = 100.0;
    m_cfg.min_len = 5000;

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
    m_shot_file = new char[FILE_NAME_LEN];
    sprintf(m_shot_file, "./sho_info.xml");
    m_fshot = fopen(m_shot_file, "w");
    string s = "<shots>\n";
    fwrite(s.c_str(), s.size(), 1, m_fshot);
#if DEBUG 
    cout << "initial ok!" << endl;
#endif

    return 0;
}

int video_split_processor::write_shot_info()
{
    stringstream ss;
    string shot_info = "\t<shot>\n\t\t<start>";
    ss << m_curr_shot.start;
    shot_info += ss.str();
    shot_info += "</start>\n\t\t<end>";
    ss.str("");
    ss << m_curr_shot.end;
    shot_info += ss.str();
    shot_info += "</end>\n\t\t<start_frame_type>";
    ss.str("");
    ss << m_curr_shot.start_frame_type;
    shot_info += ss.str();
    shot_info += "</start_frame_type>\n\t\t<end_frame_type>";
    ss.str("");
    ss << m_curr_shot.end_frame_type;
    shot_info += ss.str();
    shot_info += "<end_frame_type>\n";
    for (vector<frame_info>::const_iterator it = m_curr_shot.boundaries.begin();
            it != m_curr_shot.boundaries.end(); ++it)
    {
        shot_info += "\t\t<mid-boundary>\n\t\t\t<prev_ts>";
        ss.str("");
        ss << it->prev_ts;
        shot_info += ss.str();
        shot_info += "</prev_ts>\n\t\t\t<cut>";
        ss.str("");
        ss << it->cut;
        shot_info += ss.str();
        shot_info += "</cut>\n\t\t</mid-boundary>\n";
    }
    shot_info += "\t</shot>\n";
    fwrite(shot_info.c_str(), shot_info.size(), 1, m_fshot);


}
video_split_processor::~video_split_processor()
{
    m_curr_shot = mp_sd->flush();
    if (m_curr_shot.start > 0 and m_curr_shot.end > 0)
    {
        write_shot_info();
        cout << "end ---shot: " <<  m_curr_shot.start << ", " << m_curr_shot.end << ", " << m_curr_shot.start_frame_type << ", " << m_curr_shot.end_frame_type << endl;
    }
    m_curr_shot = mp_sd->flush();
    if (m_curr_shot.start > 0 and m_curr_shot.end > 0)
    {
        write_shot_info();
        cout << "end ---shot: " <<  m_curr_shot.start << ", " << m_curr_shot.end << ", " << m_curr_shot.start_frame_type << ", " << m_curr_shot.end_frame_type << endl;
    }

#if DEBUG
    cout << "destructor" << endl;
    cout << m_video_file << endl;

#endif
    string s = "</shots>\n";
    fwrite(s.c_str(), s.size(), 1, m_fshot);

    if (mp_sd) delete mp_sd;
    if (m_tmp_video) delete m_tmp_video;
    if (m_video_file) delete m_video_file;
    if (m_fp) 
    {
        fclose(m_fp);
        m_fp = NULL;
    }
    if (m_fshot)
    {
        fclose(m_fshot);
        m_fshot = NULL;
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
    int y_size = p_info->width * p_info->height;
    unsigned char *ybuffer = (unsigned char*)malloc(y_size);
    memset(ybuffer, 0, y_size);
    for (int i = 0; i < p_info->frame_count; ++i)
    {
        memcpy(frame_buf, mapped_buffer + i * len, len);
        //posix_memalign((void **)ybuffer, 32, y_size);
        get_Y(p_info->color_type, frame_buf, ybuffer, y_size); 


        // first time detect invoke restart after init
        if (!mb_initialized)
        {
            // 1. init video_split_processor
            // 2. create a new yuv file
            memcpy(&m_shot_begin_time, &p_info->begin_time, sizeof(live_timeval));
            mp_sd = new shot_detector((uint32_t)p_info->width, \
                    (uint32_t)p_info->height, 4, 4, m_cfg);
            memset(m_tmp_video, 0, FILE_NAME_LEN);
            sprintf(m_tmp_video, "%s/tmp_%lld_%03lld.yuv", m_video_path, \
                    p_info->begin_time.tv_sec, p_info->begin_time.tv_usec / 1000 );
            m_fp = fopen(m_tmp_video, "w+");

            mp_sd->restart(ybuffer, fts);
            //size_t s = fwrite(frame_buf, len, 1, m_fp);
            m_curr_frame_ts = fts;

            memcpy(&m_shot_begin_time, &p_info->begin_time, sizeof(live_timeval));
            mb_initialized = true;
#if DEBUG
            cout << "begintime" << m_shot_begin_time.tv_sec << "." << m_shot_begin_time.tv_usec << endl;
#endif 
        }
        else
        {
            // TODO
            // 1. detect shot
            // 2. write frame to yuv file
            // 3. frame offset

            m_curr_frame_ts +=  fts;
            cout << "frame ts: " << m_curr_frame_ts << endl;

            m_curr_shot = mp_sd->detect(ybuffer, m_curr_frame_ts);
            //fwrite(frame_buf, len, 1, m_fp);
            if (m_curr_shot.start > 0 and m_curr_shot.end > 0)
            {
                write_shot_info();
                cout << "shot info: " << m_curr_shot.start << ", " << m_curr_shot.end  << ", " <<  m_curr_shot.start_frame_type << "," << m_curr_shot.end_frame_type << endl;
                if (m_fp)
                {
                    fclose(m_fp);
                    m_fp = NULL;
                }

                memcpy(&m_shot_end_time, &p_info->begin_time, sizeof(live_timeval));

                // current shot end time
                timeval tv;
                unsigned int t_seconds = (p_info->begin_time.tv_usec +  i * fts*1000) / 1000000;
                tv.tv_usec = (p_info->begin_time.tv_usec + i * fts*1000) % 1000000;
                tv.tv_sec = p_info->begin_time.tv_sec + t_seconds;
                m_shot_end_time.tv_sec = tv.tv_sec;
                m_shot_end_time.tv_usec = tv.tv_usec;
                //rename_yuv_file();

                // next shot begin time
                tv.tv_usec = (tv.tv_usec + fts * 1000) % 1000000;
                t_seconds = (tv.tv_usec + fts * 1000) / 1000000;
                tv.tv_sec = tv.tv_sec + t_seconds;

                m_shot_begin_time.tv_sec = tv.tv_sec;
                m_shot_begin_time.tv_usec = tv.tv_usec;
                memset(m_tmp_video, 0, FILE_NAME_LEN);
                sprintf(m_tmp_video, "%s/tmp_%lld_%03lld.yuv", m_video_path, \
                        p_info->begin_time.tv_sec, p_info->begin_time.tv_usec / 1000 );
                //m_fp = fopen(m_tmp_video, "w");

            }
        }
    }
    memcpy(&m_prev_end_time, &(p_info->end_time), sizeof(live_timeval));
    // if the last video_file to deal
    memcpy(&m_shot_end_time, &(p_info->end_time), sizeof(live_timeval));

    free(ybuffer);
    return 0;
#if 0
    for(int i = 1; i < p_info->frame_count; ++i)
    {
        memcpy(frame_buf, mapped_buffer + i * len, len);
        memset(ybuffer, 0, y_size);
        get_Y(p_info->color_type, frame_buf, ybuffer, y_size); 

        m_curr_frame_ts += fts;
        m_curr_shot = mp_sd->detect(ybuffer, m_curr_frame_ts);
        fwrite(frame_buf, len, 1, m_fp);
        //cout << "=== m_shot_begin_time:" << m_shot_begin_time.tv_sec << "." << m_shot_begin_time.tv_usec << endl;

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
            unsigned int t_seconds = (p_info->begin_time.tv_usec + (i * fts)*1000 )/ 1000000;
            tv.tv_sec = p_info->begin_time.tv_sec  + t_seconds;
            tv.tv_usec = (p_info->begin_time.tv_usec + (i * fts*1000))% 1000000;
            m_shot_end_time.tv_sec = tv.tv_sec;
            m_shot_end_time.tv_usec = tv.tv_usec;

            rename_yuv_file();
            cout << "shot info: start " << m_curr_shot.start << ", " << m_curr_shot.end << endl;

            // next shot begin time
            tv.tv_usec = (tv.tv_usec + fts * 1000) % 1000000;
            t_seconds = (tv.tv_usec + fts * 1000) / 1000000;
            tv.tv_sec = tv.tv_sec + t_seconds;
            m_shot_begin_time.tv_sec = tv.tv_sec;
            m_shot_begin_time.tv_usec = tv.tv_usec;

            memset(m_tmp_video, 0, FILE_NAME_LEN);
            sprintf(m_tmp_video, "%s/tmp_%ld_%03ld.yuv", m_video_path, \
                    tv.tv_sec, tv.tv_usec / 1000);
            m_fp = fopen(m_tmp_video, "w");

        }
    }

    memcpy(&m_prev_end_time, &(p_info->end_time), sizeof(live_timeval));
    // if the last video_file to deal
    memcpy(&m_shot_end_time, &(p_info->end_time), sizeof(live_timeval));
#endif
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

}

