#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;
using namespace cv;

void showimage(const char *t, Mat& m)
{
#define SHOW 1
#if SHOW 
    imshow(t, m);
    waitKey();
#endif
}
void draw_contours(Mat &m, vector<vector<Point> >&contours)
{
    Mat tmp = Mat(m.rows, m.cols, m.type(), Scalar(0,0,0));
    for (vector<vector<Point> >::const_iterator it1 = contours.begin(); it1 != contours.end(); ++it1)
    {
        for (vector<Point>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
        {
            tmp.at<uchar>(it2->y, it2->x) = 255;
        }
    }
    showimage("tmp", tmp);
 


}
void print_contours(vector<vector<Point> > &contours)
{
    int npoints = 0;
    int nlines = 0;
    for (vector<vector<Point> >::const_iterator it1 = contours.begin(); it1 != contours.end(); ++it1)
    {
        for (vector<Point>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
        {
            cout << *it2 << " ";
            ++npoints;
        }
        cout << endl <<"++++++++++++++++++++++++++" << endl;
        ++nlines;
    }
    cout << "points is " << npoints << endl;
    cout << "lines is " << nlines << endl;
}

int main ( int argc, char *argv[] )
{
    Mat image;
    if (argc != 2 ) {
        cout << argc << "no image data\n";
        return -1;
    }
    image = imread(argv[1], 0);
    Mat t_image;
    threshold(image, t_image, 0, 255, THRESH_BINARY | THRESH_OTSU);

    showimage("t_image", t_image);
    vector <vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(t_image, contours,hierarchy, CV_CHAIN_APPROX_NONE,1);
    // 1131 points
    //findContours(t_image, contours,hierarchy, CV_RETR_TREE,1);
    showimage("contour", t_image);
    draw_contours(t_image, contours);
    print_contours(contours);
    


    return 0;
}



