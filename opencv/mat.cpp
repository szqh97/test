#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

static void help()
{
    cout << "\nThis program demonstrates line finding with the Hough transform.\n"
            "Usage:\n"
            "./houghlines <image_name>, Default is pic1.png\n" << endl;
}
int main(int argc, char** argv)
{
    const char* filename1 = argc >= 2 ? argv[1] : "pic1.png";
    const char* filename2 = argc >= 2 ? argv[2] : "pic2.png";
    double alpha = 0.5; 
    double beta;

    Mat src1 = imread(filename2 );
    if(src1.empty())
    {
        help();
        cout << "can not open " << filename1 << endl;
        return -1;
    }
    Mat src2 = imread(filename2);
    if(src1.empty())
    {
        help();
        cout << "can not open " << filename2 << endl;
        return -1;
    }
    Mat dst;
    beta = (1.0 - alpha);
    cout << alpha << ",, " << beta;
    addWeighted(src1, alpha, src2, beta, 0.5, dst);


    //Mat s = 0.5*src1 + 0.5*src2;
    imshow("average", dst);
    waitKey();
    return 0;
}

