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
#define SHOW 1

typedef vector<Point> Line;
typedef list<Line*> LineList;

void showimage(const char *t, Mat& m)
{
#if SHOW 
    imshow(t, m);
    waitKey();
#endif
}


bool check_neighbors(int x, int y, LineList &lines)
{
    cout << Point(x,y) << endl;
    bool bflag = false;
    for (LineList::iterator llit = lines.begin(); llit != lines.end(); ++llit)
    {
        cout << "the line size is: " << (*llit)->size() << &(*(*llit)->begin()) <<  " " <<&(*(*llit)->end()) << endl;
        int i = 0;
        bool f = false;
        for(Line::iterator lit = (*llit)->begin(); lit != (*llit)->end(); ++lit)
        {
            ++i;
            // left
            if (lit->x - x == -1 and lit->y == y)
            {
                //(*llit)->push_back(Point(x, y));
                bflag = true;
                f = true;
                cout << "left "<< Point(x, y) << endl;
            } 

            // top left
            if (lit->x - x == -1 and lit->y - y == -1)
            {
                //(*llit)->push_back(Point(x, y));
                bflag = true;
                f = true;
                cout << "top left "<< Point(x, y) << endl;
            }
            // top 
            if (lit->x == x and lit->y - y == -1)
            {
                //(*llit)->push_back(Point(x, y));
                bflag = true;
                f = true;
                cout << "top "<< Point(x, y) << endl;
            }
            // top right
            if (lit->x - x == 1 and lit->y - y == -1)
            {
                //(*llit)->push_back(Point(x, y));
                bflag = true;
                f = true;
                cout << "top right "<< Point(x, y) << endl;
            }
        }
        if (f)
        {
            (*llit)->push_back(Point(x,y));
        }
    }

    if (!bflag)
    {
        cout << "Create a new line " << Point(x, y)<< endl;
        Line *pl = new Line(); 
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
                cout << "invoke gen_linechains " << Point(c, r) << endl;
                check_neighbors(c, r, lines);
            }
        }
    }
    cout << "the white point num is" << i << endl;
}

void print_linecollections(LineList &lines)
{
#define PRINT_LINES 1
#if PRINT_LINES
    cout << "size: "<< lines.size() << endl;
    for (LineList::iterator llit = lines.begin(); llit != lines.end(); ++llit)
    {
        for(Line::iterator lit = (*llit)->begin(); lit != (*llit)->end(); ++lit)
        {
            cout << *lit << " ";
        }
        cout << endl <<"=============================" << endl;
    }
#endif
 

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

    LineList linecollections;

    gen_linechains(dst, linecollections);
    cout << linecollections.size() << endl;
    print_linecollections(linecollections);


    return 0;
}			/* ----------  end of function main  ---------- */


