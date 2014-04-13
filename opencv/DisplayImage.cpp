#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main ( int argc, char *argv[] )
{
    Mat image;
    if (argc != 2 ) {
        cout << argc << "no image data\n";
        return -1;
    }
    image = imread(argv[1], 1);
    namedWindow("Display Image",CV_WINDOW_AUTOSIZE);
    imshow("display image", image);
    waitKey(0);
    
    return 0;
}			/* ----------  end of function main  ---------- */


