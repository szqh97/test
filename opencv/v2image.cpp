 #include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int main ( int argc, char *argv[] )
{
    Mat image;
    if (argc != 2 ) {
        cout << argc << "no image data\n";
        return -1;
    }
    image = imread(argv[1], 0);
    Mat J;
    cv::threshold(image, J, 0, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);
    imshow("origin", image);
    imshow("after", J);
    waitKey();
 
    return 0;
}

