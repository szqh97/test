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
    IplImage Iimpl= I;

    //imshow("1",I); 
    //waitKey();
    //uchar *data =I.data;
    uchar *data =(uchar*)Iimpl.imageData;
    int step = Iimpl.widthStep/sizeof(uchar);

    vector<int> rpos;
    {
        uchar pprev =0, pcur = 0;
        for (int r = 0; r < I.rows; ++r)
        {
            pcur = 0;
            for (int c = 0; c <I.cols; ++c)
            {
                pcur |= I.at<uchar>(r, c);
                //pcur |=  uchar(data[r * I.cols  +c]);
            }
            if (pprev != pcur)
            {
                rpos.push_back(r);
            }
            pprev = pcur;
        }
    }

    vector<int> cpos;
    {
        uchar pprev =0, pcur = 0;
        for (int c = 0; c < I.cols; ++c)
        {
            pcur = 0;
            for (int r = 0; r < I.rows; ++r)
            {
                pcur |= I.at<uchar>(r, c);
                //pcur |=  uchar(data[r * I.cols  +c]);
            }
            if (pprev != pcur)
            {
                cpos.push_back(c);
            }
            pprev = pcur;
        }
    }

#if 1
    for (int i = 0; i < rpos.size(); i+=2)
    {

        for (int j = 0; j < cpos.size(); j+=2)
        {
            //cout << "[(" << rpos[i] << "," << cpos[j] << "), (" << rpos[i +1] << "," << cpos[j + 1] << ")]" << endl;
            Point p1 = Point(double(rpos[i]), double(cpos[j]));
            Point p2 = Point(double(rpos[i+1]), double(cpos[j+1]));
            //rects.insert(pair<Point, Point>(Point(rpos[i], cpos[j]), Point(rpos[i+1], cpos[j+1])));
            cout << p1 << "|" <<p2 <<endl;
            rectangle(image, p1, p2, Scalar(0,0,255), 0, 8);
            
        }
    }
#endif 
    namedWindow("1"); 
    imshow("1",image); 
    waitKey();


#if 0
    for (size_t i = 0;  i < rpos.size(); ++i)
    {
            cout << rpos[i] << endl;

    }

    cout << "----------------" << endl;

    for (size_t i = 0; i < cpos.size(); ++i)
    {
        cout << cpos[i] << endl;
    }

#endif
    return 0;
}
