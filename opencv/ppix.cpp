#include <iostream>
#include <stdio.h>
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

    int *hist_w = new int[image.cols];
    int *hist_h = new int[image.rows];
    memset(hist_h, 0, image.rows* sizeof(int));
    memset(hist_w, 0, image.cols* sizeof(int));

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

    {
        uchar pprev =0, pcur = 0;
        for (int r = 0; r < I.rows; ++r)
        {
            pcur = 0;
            for (int c = 0; c <260; ++c)
            //for (int c = 0; c <I.cols; ++c)
            {
                pcur |= I.at<uchar>(r, c);
                if (I.at<uchar>(r,c) >0)
                {
                    hist_w[c] = 1;
                    hist_h[r] = 1;
                }
                //pcur |=  uchar(data[r * I.cols  +c]);
            }
        }
    }

#if 1
    vector<int> rpos;
    {
        for (int i=0; i < image.rows-1; ++i)
        {

            if(hist_h[i] != hist_h[i+1])
            {

                rpos.push_back(i);
                line(image, Point(0, i), Point(image.cols , i), Scalar(0,0,255), 1, CV_AA);
                cout << i << ", " ;
            }
        
        }
    }
    vector<int> cpos;
    {
        for (int i=0; i < image.cols-1; ++i)
        {
            if(hist_w[i] != hist_w[i+1])
            {
                cpos.push_back(i);
                line(image, Point(i, 0), Point(i, image.rows ), Scalar(0,0,255), 1, CV_AA);
            }

        }
    } 
#endif

#if 0 
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
#endif
    Mat blank = Mat(image.rows*3, image.cols* 3, image.type(), Scalar(255, 255, 255));
    imshow("blank", blank);
    waitKey();
    for (size_t i = 0; i < cpos.size(); i +=2)
    {
        Mat w;
        Rect ROI(cpos[i], 0, cpos[i+1] - cpos[i], image.rows);
        image(ROI).copyTo(w);
        Size dsize = Size(w.cols * 2, w.rows*2);
        Mat rw = Mat(dsize, w.type());
        resize(w, rw, dsize, 0, 0, INTER_CUBIC);
        /*  
        imshow("a", rw);
        waitKey();
        */


    }

#if 0
    Mat w;
    int wc = 0;
    for (int i = 0; i < rpos.size(); i+=2)
    {

        for (int j = 0; j < cpos.size(); j+=2)
        {

            //cout << "[(" << rpos[i] << "," << cpos[j] << "), (" << rpos[i +1] << "," << cpos[j + 1] << ")]" << endl;
            Point p1 = Point(double(cpos[j]), double(rpos[i]));
            Point p2 = Point(double(cpos[j+1]), double(rpos[i+1]));
            //rects.insert(pair<Point, Point>(Point(rpos[i], cpos[j]), Point(rpos[i+1], cpos[j+1])));
            //cout << p1 << "|" <<p2 <<endl;
            //rectangle(image, p2, p1, Scalar(0,0,255), 0, 1);

            // get sub rect of word
            cvGetSubRect(&cvimage, &cvw, cvRect(p1.x, p1.y, p2.x - p1.x, p2.y - p1.y));
            Size dsize = Size(Mat(&cvw).cols * 5 , Mat(&cvw).rows * 5);
            Mat dstw = Mat(dsize,Mat(&cvw).type());
            resize(Mat(&cvw), dstw, dsize, 0, 0, INTER_LANCZOS4);
            ++wc;
            {
                char fname[18];
                sprintf(fname,"a%07d.tif", wc);
                //imwrite(fname, dstw);
            }

        }
    }
#endif

#if 1
    namedWindow("1"); 
    imshow("1",image); 
    waitKey();
#endif

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
    delete []hist_w;
    delete []hist_h;
    return 0;
}
