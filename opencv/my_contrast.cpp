#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace std;
using namespace cv;
double alpha;
int beta;

int main ( int argc, char *argv[] )
{
    Mat image = imread(argv[1]);
    Mat new_image = Mat::zeros(image.size(), image.type());
    cout << "Basic linear trasforms" << endl;
    cout << "-----------------------" << endl;
    cout << "the alpha values[1.0-3.0]:" ; cin >> alpha;
    cout << "Enter the beta value[0-100]:" ; cin >> beta;
    for (int  y = 0; y < image.rows; ++y)
    {
        for (int x = 0; x < image.cols; ++x)
        {
            for (int c = 0; c < image.channels(); ++c)
            {
                new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y,x)[c]) + beta);
            }
        }
    }

    namedWindow("Original Image", 1);
    imshow("Original image", image);
    
    namedWindow("New Image", 1);
    imshow("New Image", new_image);
    waitKey();
    return 0;
}			/* ----------  end of function main  ---------- */

