#include <iostream>
#include <string>
#include <stdint.h>
extern "C"{
#include <libavformat/avformat.h>
#include <libavutil/dict.h>
}
using namespace std;

int main ( int argc, char *argv[] )
{
    av_register_all();
    int ret = -1;
    AVFormatContext *pFormatCtx = NULL;
    AVDictionaryEntry *tag = NULL;
    string filename = "./tear.mp3";
    //string filename = "./test.flv";
    ret = avformat_open_input(&pFormatCtx, filename.c_str(), NULL, NULL);
    if (ret)
    {
        cerr << "open file: " << filename << "error" << endl;
    }

    while((tag = av_dict_get(pFormatCtx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX)))
        cout << tag->key << "=" << tag->value << endl;

    avformat_close_input(&pFormatCtx);
    return 0;
}			/* ----------  end of function main  ---------- */

