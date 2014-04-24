 #include <iostream>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void add ( Mat & f, int *c, int width, int heght);
void average(int *c, Mat &avf, int framecount);
int main ( int argc, char *argv[] )
{
    VideoCapture cap("./t.mp4");
    int width =cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int *c = new int[width * height];
    int framecount = 0;
    Mat sumframe;
    Mat  f_, f, avf;
    f.create(height, width, CV_8UC1);
    avf.create(height, width, CV_8UC1);
    unsigned int framenum =0;
    bool quit = false;
#if 0
    cap >>f0_;
    cvtColor(f0_, f0, CV_BGR2GRAY);
    cap >>f_; 
    cvtColor(f_, f, CV_BGR2GRAY);
    if (f0.empty() or f.empty())
    {
        return 1;
    }
    add(f0, f, sumframe);
#endif
    while (!quit)
    {
        cap >>f_;
        if (f_.empty())
        {
            quit = true;
        }
        ++framecount;
        cout << "aaaaa";
        cvtColor(f_, f, CV_BGR2GRAY);

        add(f,c, width, height );
        average(c, avf, framecount);
        imshow("aaa", avf);
        waitKey();
        cout << "aAaa" << endl;
    }


    return 0;
}

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
