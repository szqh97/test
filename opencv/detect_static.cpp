/**************************************************
 * 背景建模，运动物体检测
 *      
 **************************************************/

/***********************************************************************
 * OpenCV example
 * By Shiqi Yu 2006
 ***********************************************************************/


#include <iostream>
#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
    //声明IplImage指针
    IplImage* pFrame = NULL; 
    IplImage* pFrImg = NULL;
    IplImage* pBkImg = NULL;

    CvMat* pFrameMat = NULL;
    CvMat* pFrMat = NULL;
    CvMat* pBkMat = NULL;

    CvCapture* pCapture = NULL;

    int nFrmNum = 0;



    if( argc > 2 )
    {
        fprintf(stderr, "Usage: bkgrd [video_file_name]\n");
        return -1;
    }

    //打开视频文件
    if(argc == 2)
        if( !(pCapture = cvCaptureFromFile(argv[1])))
        {
            fprintf(stderr, "Can not open video file %s\n", argv[1]);
            return -2;
        }

    cvSetCaptureProperty(pCapture,CV_CAP_PROP_FRAME_COUNT, 500);
    //逐帧读取视频
    while(pFrame = cvQueryFrame( pCapture ))
    {
        nFrmNum++;

        //如果是第一帧，需要申请内存，并初始化
        if(nFrmNum == 1)
        {
            pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);
            pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);

            pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
            pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
            pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);

            //转化成单通道图像再处理
            cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);
            cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);

            cvConvert(pFrImg, pFrameMat);
            cvConvert(pFrImg, pFrMat);
            cvConvert(pFrImg, pBkMat);
        }
        else
        {
            cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
            cvConvert(pFrImg, pFrameMat);
            //高斯滤波先，以平滑图像
            //cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);

            //当前帧跟背景图相减
            cvAbsDiff(pFrameMat, pBkMat, pFrMat);

            //二值化前景图
            cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);

            //进行形态学滤波，去掉噪音  
            cvErode(pFrImg, pFrImg, 0, 1);
            cvDilate(pFrImg, pFrImg, 0, 1);

            //更新背景
            cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);
            //将背景转化为图像格式，用以显示
            //cvConvert(pBkMat, pBkImg);

            //显示图像
           // cvShowImage("video", pFrame);
            //cvShowImage("background", pBkImg);
           // cvShowImage("foreground", pFrImg);

            //如果有按键事件，则跳出循环
            //此等待也为cvShowImage函数提供时间完成显示
            //等待时间可以根据CPU速度调整

        }

    }

    if (countNonZero(Mat(pFrImg)) < 1)
        cout << "Mat is zero" << endl;


    //释放图像和矩阵
    cvReleaseImage(&pFrImg);
    cvReleaseImage(&pBkImg);

    cvReleaseMat(&pFrameMat);
    cvReleaseMat(&pFrMat);
    cvReleaseMat(&pBkMat);

    cvReleaseCapture(&pCapture);

    return 0;
}
