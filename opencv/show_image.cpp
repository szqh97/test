  #include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
  
using namespace cv;  
using namespace std;

int main ( int argc, char *argv[] )
{

    if (argc <= 1 )
    {
        cout << "Usage: show_image x.jpg" << endl;
        return 1;
    }
    Mat img=imread(argv[1]);  
    cvNamedWindow("test");  
    imshow("test",img);  
    waitKey(3000);  
    return 0;
}			/* ----------  end of function main  ---------- */
  
