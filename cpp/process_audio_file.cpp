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
//char name_buffer[] = "/home/li_yun/example/20130607_075150.233627.audio";
char name_buffer[] = "20130608_021945.238344.audio";
int process_audio_file ()
{
    FILE *fp = fopen(name_buffer, "r");
    if (!fp)
    {
        cerr << "Open file " << name_buffer << " failes" << endl;
        return 0;
    }
    ssize_t offset = sizeof(audio_file_info);
    cout << "offset is " << offset << endl;
    int ret = fseek(fp, -offset, SEEK_END);
    if (ret)
    {
        cerr << "fseek failes" << endl;
        fclose(fp);
        return -1;
    }

    off_t post = ftello(fp);
    cout << "pos " << post;
    audio_file_info info; 
    ret = fread(&info, offset, 1, fp);
    if (ret != 1)
    {
        cerr << "Read file fails" << endl;
        fclose(fp);
        return -1;
    }
    cout << "bit : " << info.bit << ", channel : " << info.channel \
         << ", rate: " << info.rate << ", begin_time: " << \
         info.begin_time.tv_sec << "." << info.begin_time.tv_usec \
         << ", end_time: " << info.end_time.tv_sec << "." << \
         info.end_time.tv_usec << endl;
    fclose(fp);

    
}

const char video_file_name[] = "20130607_075150.218767.video";
char *video_file_name = argv[1];

int process_video_file()
{
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
    cout << "position : " << pos << " width : " << info.
        width << " height: " << info.height << " frame rate : " << info.
        frame_rate << " frame_count : " << info.frame_count << " begin_time : " << info.
        begin_time.tv_sec << "." << info.begin_time.tv_usec << " end_time : " << info.end_time.
        tv_sec << "." << info.end_time.
        tv_usec << endl;
        if ( (info.begin_time.tv_usec - info.end_time.tv_usec ) < 0)
        {
            cout << "aa" << endl;
        }

    config cfg;
    cfg.hist_th = 0.5;
    cfg.diff_cnt_th =  5;
    cfg.var_th = 100.0;
    shot_detector sd ((uint32_t)info.width, (uint32_t)info.height, 4, 4, cfg);

    off_t len = pos / info.frame_count;
    size_t mapped_size = 0;
    unsigned char *mapped_buffer = map_file(fp,  len * (int)info.frame_count, mapped_size);

    unsigned long begin_ts = 1;
    unsigned long end_ts = info.frame_count * (1000/info.frame_rate);
    unsigned char * frame_buffer = (unsigned char*) malloc(info.width * info.height* 2);
    memset(frame_buffer, 0, len);
    memcpy(frame_buffer, mapped_buffer,  len);
    int i = 0; 
    gettimeofday(&t1, NULL);
    sd.restart(frame_buffer, 40);
    
    for (i = 1; i < info.frame_count; ++i)
    {
        memcpy(frame_buffer, mapped_buffer + i*len, len);
        unsigned long start_ts = i * 40;
        shot st = sd.detect(frame_buffer, start_ts); 
         cout <<"shot info start:" << st.start << ", shot end: " << st.end << \
             ", start type: " << st.start_frame_type << ", end type: " << \
             st.end_frame_type << endl;
        
    }
    shot st = sd.flush();
    /*
    cout <<"shot info start:" << st.start << ", shot end: " << st.end << \
         ", start type: " << st.start_frame_type << ", end type: " << \
         st.end_frame_type << endl;
    */
    gettimeofday(&t2, NULL);
    cout << "t1:" << t1.tv_sec <<"." << t1.tv_usec << " " << "t2:" << \
            t2.tv_sec << "." << t2.tv_usec << endl;


    free(frame_buffer);

    
    fclose(fp);
}

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
    mapped_size = aligned_size;
    return addr;
}

int main ( int argc, char *argv[] )
{
    cout << "the length of audio_file_info is " << sizeof(audio_file_info) << endl;
    process_audio_file();
    cout << "video \n" ;
    process_video_file();
    return 0;
}			/* ----------  end of function main  ---------- */
