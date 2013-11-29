#include <iostream>
#include <sys/time.h>
#include <stdint.h>
#include <cstdio>
#include <iomanip>
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

//const char video_file_name[] = "20130607_075150.218767.video";
int process_video_file(char *video_file_name)
{
    FILE *fp = fopen(video_file_name, "r");
    if (!fp)
    {
        cerr << "Open file " << video_file_name << " fails" << endl;
        return -1;
    }
    size_t offset = sizeof(video_file_info);
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
        begin_time.tv_sec << "." << setfill('0') << setw(6) << info.begin_time.tv_usec 
        << " end_time : " << info.end_time. tv_sec << "." << setfill('0') << setw(6) << 
        info.end_time. tv_usec << endl;
        if ( (info.begin_time.tv_usec - info.end_time.tv_usec ) < 0)
        {
            cout << "aa" << endl;
            }
    fclose(fp);
}

int main ( int argc, char *argv[] )
{
    cout << "the length of audio_file_info is " << sizeof(audio_file_info) << endl;
    //process_audio_file();
    cout << "video \n" ;
    for (int i=1; i < argc; ++i)
    {
        process_video_file(argv[i]);

    }
    return 0;
}			/* ----------  end of function main  ---------- */
