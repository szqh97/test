#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main ( int argc, char *argv[] )
{
    if (argc != 2)
    {
        cout << "Usage :" << argv[0] << " ImageToLoadAndDisplay" << endl;
        return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    if (!image.data)
    {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    namedWindow("Display window", CV_WINDOW_AUTOSIZE);
    imshow("Display window", image);
    waitKey(0);
    return 0;
}			/* ----------  end of function main  ---------- */

