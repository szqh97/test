// Example that shows simple usage of the INIReader class

#include <iostream>
#include <string.h>
#include "INIReader.h"
#include <sstream>
using namespace std;
#define TOSTR(x) "video" #x
#define TOSECTION(x) "video" #x            /*  */

int main()
{
    INIReader reader("./shotdetect.conf");
    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'live_box.conf'\n";
        return 1;
    }
    int channelid = 1;
    stringstream ss;

    ss <<"video" << channelid;
    double var_th, hist_th;
    int diff_cnt_th, block_h, block_w, width, height;
    var_th = reader.GetReal(ss.str().c_str(), "var_th", 1.0);
    hist_th = reader.GetReal("video1", "hist_th", 0.5);
    diff_cnt_th = reader.GetInteger("video1", "diff_cnt_th", 5);
    block_h = reader.GetInteger("video1", "block_h", 4);
    block_w = reader.GetInteger("video1", "block_w", 4);
    width = reader.GetInteger("video1", "width", 0);
    height = reader.GetInteger("video1","height", 0);
    cout << "var_th: " << var_th << endl;
    cout << "hist_th: " << hist_th<< endl;
    cout << "diff_cnt_th: " << diff_cnt_th<< endl;
    cout << "block_h: " << block_h<< endl;
    cout << "block_w: " << block_w<< endl;
    cout << "width: " << width<< endl;
    cout << "height: " << height<< endl;


    /* 
    block_h = 4
block_w = 4
diff_cnt_th = 5
height = 0
hist_th = 0.5
max_len = 70000
min_len = 60000
var_th = 100.0
width = 0
*/


        /*
              << reader.GetInteger("protocol", "version", -1) << ", name="
              << reader.Get("user", "name", "UNKNOWN") << ", email="
              << reader.Get("user", "email", "UNKNOWN") << ", pi="
              << reader.GetReal("user", "pi", -1) << ", active="
              << reader.GetBoolean("user", "active", true) << "\n";
          */
    return 0;
}
