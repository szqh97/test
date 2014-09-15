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
    
    VideoCapture cap("./t.mp4");
    int width =cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    cout << cap.set(CV_CAP_PROP_POS_FRAMES, 10) <<endl;
    
    bool quit = false;
    int cnt = 0;
    int histSize = 255;
    float range[] = { 0, 255 } ;
    const float* histRange = { range };
    Mat f, f_, hist;
    int *c = new int[width * height];
    f.create(height, width, CV_8UC1);
    while (!quit)
    {
        ++cnt;
        cap >>f_;
        cout << "read from cap" << endl;
        if (f_.empty())
        {
            quit = true;
        }

        cout << cap.set(CV_CAP_PROP_POS_FRAMES, cnt * 2);
        cvtColor(f_, f, CV_BGR2GRAY);

        calcHist( &f, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);
        normalize(hist, hist, 0, width, NORM_MINMAX, -1, Mat());
        cout << hist << endl;
#if 0
        if (cnt ==10)
        {
        quit = true;
        }
#endif

    }


    return 0;
}			/* ----------  end of function main  ---------- */


