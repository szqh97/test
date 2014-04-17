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

    if (image.isContinuous()) 
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

    //imshow("1", image); 
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
    for (size_t i = 0;  i < pixs.size()-1; ++i)
    {
        if (pixs[i] != pixs[i+1])
        {
            cout << i+1 << endl;
        }

    }

#if 0
    cout << pixs.size() << endl;
    for (vector<uchar>::const_iterator it = pixs.begin(); it != pixs.end(); ++it)
    {
        cout << int(*it) << endl ; 
    }
#endif
 

    return 0;
}
#if 0

void colorReduce(const cv::Mat& image, cv::Mat& result, int div)
{
    int nl = image.rows;
    int nc = image.cols * image.channels();

    if (image.isContinuous()) {
        nc = nc * nl;
        nl = 1;
    }

    int n = static_cast<int>(
        log(static_cast<double>(div)) / log(2.0));

    for (int j = 0; j < nl; j++) {
        // get the addresses of input and output row
        const uchar *data_in = image.ptr<uchar>(j); //give you the address of an image row
        uchar *data_out = result.ptr<uchar>(j);

        for (int i = 0; i < nc; i++) {
            
            //slowest
            data[i] = data[i] - data[i] % div + div / 2;
            //middle
            data[i] = data[i] / div * div + div / 2;
            //best
            uchar mask = 0xFF << n; //div = 16, n = 4, mask = 0xF0
            data_out[i] = (data_in[i] & mask) + div / 2; //data[i] - data[i] % div + div / 2
        }
    }
}
#endif
