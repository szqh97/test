#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
int main ( int argc, char *argv[] )
{
    Mat image;
    Mat dst;
    if (argc != 2 ) {
        cout << argc << "no image data\n";
        return -1;
    }
    image = imread(argv[1], 0);
    Canny(image, dst, 50, 150, 3);
    imshow("origin", image);
    imshow("edge-detect", dst);
    waitKey();

    return 0;
}
