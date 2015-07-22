#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
#include <iostream>

using namespace std;
using namespace cv;


int main ( int argc, char *argv[] )
{
    char* imageName = argv[1];
    Mat image;
    image = imread(imageName, 1);

    if (argc != 2 || !image.data)
    {
        cout << "No image data \n" << endl;
        return -1;
    }

    Mat gray_image;
    cvtColor(image, gray_image, CV_RGB2GRAY);

    imwrite("/tmp/gray_image.jpg", gray_image);
    namedWindow(imageName, CV_WINDOW_AUTOSIZE);
    namedWindow("Gray image", CV_WINDOW_AUTOSIZE);


    imshow(imageName, image);
    imshow("Gray image", gray_image);
    waitKey(0);
    return 0;
}			/* ----------  end of function main  ---------- */

