#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;
using namespace cv;

void add ( Mat & f, int *c, int width, int heght)
{
    MatIterator_<uchar> it ;
    int i = 0;
    for (it =  f.begin<uchar>(); it != f.end<uchar>(); ++it)
    {
        if (i < width*heght)
        {
            c[i++] += *it;
        }
    }
}


void average(int *c, Mat &avf, int framecount)
{
    int size = avf.rows * avf.cols;
    MatIterator_<uchar> it;
    int i = 0;
    for (it = avf.begin<uchar>(); it != avf.end<uchar>(); ++it)
    {
        *it = c[i++];
    }
}
int main ( int argc, char *argv[] )
{
    
    VideoCapture cap("./o.avi");
    int width =cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    bool quit = false;
    int framecount = 0;
    Mat f, f_;
    int *c = new int[width * height];
    f.create(height, width, CV_8UC1);
    while (!quit)
    {
        cap >>f_;
        if (f_.empty())
        {
            quit = true;
        }
        if (framecount % 5 == 0)
        {
            cvtColor(f_, f, CV_BGR2GRAY);

        }
        ++framecount;
        add(f,c, width, height );
    }


    return 0;
}			/* ----------  end of function main  ---------- */


