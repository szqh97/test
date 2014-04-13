#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
void Sharpen(const Mat& myImage, Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U); //accept only uchar images
    Result.create(myImage.size(), myImage.type());
    const int nChannels = myImage.channels();

    for (int j = 1; j < myImage.rows-1; ++j)
    {
        const uchar *previous = myImage.ptr<uchar>(j-1);
        const uchar *current  = myImage.ptr<uchar>(j  );
        const uchar *next     = myImage.ptr<uchar>(j+1);

        uchar *output = Result.ptr<uchar>(j);

        for (int i = nChannels; i < nChannels*(myImage.cols - 1); ++i)
        {
            *output++ = saturate_cast<uchar>(5*current[i] 
                    - current[i-nChannels] - current[i+nChannels] - previous[i] - next[i]);
        }
    }
    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows -1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols - 1).setTo(Scalar(0));
}


int main ( int argc, char *argv[] )
{

    Mat image;
    if (argc != 2 ) {
        cout << argc << "no image data\n";
        return -1;
    }
    
    Mat kern = (Mat_<char>(3,3) <<  0, -1,  0,
                                   -1,  60, -1,
                                    0, -1,  0);
    image = imread(argv[1], 1);
    Mat j; 
    //Sharpen(image, j);
    filter2D(image, j, image.depth(), kern);
    imshow("display image", j);
    waitKey();

    return 0;
}			/* ----------  end of function main  ---------- */

