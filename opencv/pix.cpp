#include <iostream>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
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

    if (!image.isContinuous()) 
    {
    }
    Mat J;
    Mat I;

    uchar table[256];
    int divideWith = 10;
    for (int i = 0; i < 256; ++i)
      table[i] = (uchar)(divideWith * ((255-i)/divideWith));

    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data;
    for( int i = 0; i < 256; ++i)
        p[i] = table[i];
    LUT(image, lookUpTable, J);

    cv::threshold(J, I, 0, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);

    //imshow("1",I); 
    //waitKey();
    uchar *data =I.data;

    vector<uchar> pixs;
    for (int r = 0; r < I.rows; ++r)
    {
        uchar p = 0;
        for (int c = 0; c <I.cols; ++c)
        {
           p |=  uchar(data[r * I.cols  +c]);
        }
        pixs.push_back(p);
    }

    vector<uchar> cpos;
    for (int c = 0; c < I.cols; ++c)
    {
        uchar p = 0;
        for (int r = 0; r < I.rows; ++r)
        {
           p |=  uchar(data[r * I.cols  +c]);
        }
        cpos.push_back(p);
    }

#if 0
    for (size_t i = 0;  i < pixs.size()-1; ++i)
    {
        if (pixs[i] != pixs[i+1])
        {
            cout << i+1 << endl;
        }

    }
#endif

    for (size_t i = 0; i < cpos.size() -1; ++i)
    {
        if (cpos[i] != cpos[i+1])
        {
            cout << i+1 << endl;
        }
    }

    return 0;
}
