#include "video_split.h"
#include <unistd.h>
#include <string>
#include <fstream>
#include <iomanip>

int main ( int argc, char *argv[] )
{

    ifstream vfile("t.out");
    string video_file_name;
    while(vfile >> video_file_name)
    {
        //const char *video_file_name = "20131129_053145.336953.video";
        // for test
        struct timeval t1, t2;
        FILE *fp = fopen(video_file_name.c_str(), "r");
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
        //cout <<  " color type: " << info.color_type << endl;

    }

    return 0;
}			/* ----------  end of function main  ---------- */
