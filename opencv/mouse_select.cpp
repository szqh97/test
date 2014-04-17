 #include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <stdio.h>
#include <iostream>

#pragma comment( lib, "opencv_highgui241d.lib" )
#pragma comment( lib, "opencv_core241d.lib" )
#pragma comment( lib, "opencv_ml241d.lib" )
#pragma comment( lib, "opencv_imgproc241d.lib" )
#pragma comment( lib, "opencv_objdetect241d.lib" )
#pragma comment( lib, "opencv_features2d241d.lib")
#pragma comment( lib, "opencv_calib3d241d.lib")
#pragma comment( lib, "opencv_nonfree241d.lib")
#pragma comment( lib, "opencv_flann241d.lib")

using namespace cv;
using namespace std;
Rect selectRect;
bool select_flag=false;
Point origin;
Mat frame;

/************************************************************************************************************************/
/****                            如果采用这个onMouse()函数的话，则可以画出鼠标拖动矩形框的4种情形                        ****/
/************************************************************************************************************************/
void onMouse(int event,int x,int y,int,void*)
{
    //Point origin;//不能在这个地方进行定义，因为这是基于消息响应的函数，执行完后origin就释放了，所以达不到效果。
    if(select_flag) {
        selectRect.x=MIN(origin.x,x);//不一定要等鼠标弹起才计算矩形框，而应该在鼠标按下开始到弹起这段时间实时计算所选矩形框
        selectRect.y=MIN(origin.y,y);
        selectRect.width=abs(x-origin.x);//算矩形宽度和高度
        selectRect.height=abs(y-origin.y);
        selectRect&=Rect(0,0,frame.cols,frame.rows);//保证所选矩形框在视频显示区域之内
    }
    if(event==CV_EVENT_LBUTTONDOWN) {
        select_flag=true;//鼠标按下的标志赋真值
        origin=Point(x,y);//保存下来单击是捕捉到的点
        selectRect=Rect(x,y,0,0);//这里一定要初始化，宽和高为(0,0)是因为在opencv中Rect矩形框类内的点是包含左上角那个点的，但是不含右下角那个点
    } else if(event==CV_EVENT_LBUTTONUP) {
        select_flag=false;
    }
}

int main(int argc, unsigned char* argv[])
{
    char c;

    //打开摄像头
    VideoCapture cam(0);
    if (!cam.isOpened())
        return -1;

    //建立窗口
    namedWindow("camera",1);//显示视频原图像的窗口
    //捕捉鼠标
    setMouseCallback("camera",onMouse,0);

    while(1) {
        //读取一帧图像
        cam>>frame;
        if(frame.empty())
            return -1;

        //画出矩形框
        rectangle(frame,selectRect,Scalar(255,0,0),3,8,0);//能够实时显示在画矩形窗口时的痕迹

        //显示视频图片到窗口
        imshow("camera",frame);

        //select.zeros();
        //键盘响应
        c=(char)waitKey(20);
        if(27==c)//ESC键
            return -1;
    }
    return 0;
}

