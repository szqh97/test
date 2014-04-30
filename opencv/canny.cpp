#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using namespace cv;
#define SHOW 1

typedef vector<Point> Line;
typedef vector<Line*> LineList;

void showimage(const char *t, Mat& m)
{
#if SHOW 
    imshow(t, m);
    waitKey();
#endif
}


bool check_neighbors(int x, int y, LineList &lines)
{
    bool bflag = false;
    for (LineList::iterator llit = lines.begin(); llit != lines.end(); ++llit)
    {
        for(Line::iterator lit = (*llit)->begin(); lit != (*llit)->end(); ++lit)
        {
            if (lit->x - x == 1 or lit->x -x == -1 or lit->y - y == 1 or lit->y - y == -1)
            {
                Line *pl = new Line;
                pl->push_back(Point(x, y));
                //(*llit).push_back(Point(x, y));
                bflag = true;
                //cout << "xxxxxxxx " << x <<", " << y << endl;
            }
        }
    }

    if (!bflag)
    {
        Line *pl = new Line; 
        pl->push_back(Point(x, y));
        lines.push_back(pl);
    }
    return true;

}

int gen_linechains(const Mat &m, LineList &lines)
{
    int i = 0; 
    cout << m.type() << endl; 
    cout << m.channels() << endl;
    for (int r = 0; r < m.rows; ++r)
    {
        for (int c = 0; c < m.cols; ++c)
        {
            if ((int)m.at<uchar>(r, c) == 255 )
            {
                ++i;
                check_neighbors(c, r, lines);
            }
        }
    }
    cout << "xx" << i << endl;
}

void print_linecollections(LineList &lines)
{
    cout << "size: "<< lines.size() << endl;
    for (LineList::iterator llit = lines.begin(); llit != lines.end(); ++llit)
    {
        for(Line::iterator lit = (*llit)->begin(); lit != (*llit)->end(); ++lit)
        {
            cout << *lit << " ";
        }
        cout << endl <<"=============================" << endl;
    }
 

}
int main ( int argc, char *argv[] )
{
    Mat image;
    if (argc != 2 ) {
        cout << argc << "no image data\n";
        return -1;
    }
    image = imread(argv[1], 0);

    Mat dst;
    Canny(image, dst, 50, 150, 3);
    imwrite("bb.png", dst);
    cout <<  "aaaaaaaaaaaa" << dst.cols << ", " << dst.rows << endl;
    cout << "xxxxxxxxxxxxxxxx" << endl;
    cout << "xxxxxxxxxxxxxxxx" << endl;

    LineList linecollections;

    gen_linechains(dst, linecollections);
    cout << linecollections.size() << endl;
    print_linecollections(linecollections);


    return 0;
}			/* ----------  end of function main  ---------- */


