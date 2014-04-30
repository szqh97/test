#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

void crop_pic(char *filename, unsigned int posx, unsigned int posy, unsigned int width, unsigned int height, Mat &dst)
{
    Mat src = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    Rect ROI(posx, posy, width, height);
    src(ROI).copyTo(dst);
}


int main ( int argc, char *argv[] )
{
    Mat m;
    crop_pic(argv[1], atoi(argv[2]), atoi(argv[3]),atoi(argv[4]),atoi(argv[5]), m);
    imwrite("aa.tif", m);
    imshow("aa",m);
    waitKey();

    return 0;
}			/* ----------  end of function main  ---------- */

