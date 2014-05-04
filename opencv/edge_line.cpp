#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
using namespace cv;
#define SHOW 1
class Line{
    public:
        Point2f centriod;
        Point2f vertex;
        double width;
        double height;
        unsigned int n;
        double grey;
        friend bool operator < (const Line &ls, const Line &rs);

};
inline bool operator < (const Line &ls, const Line &rs)
{
    return ((ls.vertex.x < rs.vertex.x and ls.vertex.y < rs.vertex.y)
            or (ls.width*ls.height < rs.width * rs.height)
            or (ls.n < rs.n )
            or (ls.grey < rs.grey)
        );
}

void showimage(const char *t, Mat& m)
{
#if SHOW 
    imshow(t, m);
    waitKey();
#endif
}

void print_lchains(const map<Line, vector<Point> > &lines)
{
    cout << "sssss" << endl;
    for (map<Line, vector<Point> >::const_iterator it = lines.begin(); it != lines.end(); ++it)
    {
        Line l = it->first;
        cout << "centriod: " << l.centriod << " "
            << "vertex: " << l.vertex << " "
            << "width: " << l.width << " "
            << "height: " << l.height << " "
            << "n: "<< l.n << " "
            << "grey: " << l.grey << endl;
    }
}

double line_length(const Point2f &p1, const Point2f &p2)
{

//    cout << " __________ " << p1 << " " << p2 << endl;
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx*dx + dy*dy);
}

double get_average_grey(const Mat &orgin_m, Rect &roi)
{
    Mat m(orgin_m, roi);

    unsigned long long grey_sum = 0;
    for(int r = 0; r < m.rows; ++r)
    {
        for (int c = 0; c < m.cols; ++c)
        {
           grey_sum += m.at<uchar>(r, c);
        }
    }
    return (double)grey_sum/(m.cols * m.rows);
}

void get_line(Mat &orig_m, Mat &m, map<Line, vector<Point> > &lchains)
{

    vector <vector<Point> > contours;
    // findContours would modify the original mat, 
    findContours(m, contours, CV_CHAIN_APPROX_NONE, 1);

    for (vector<vector<Point> >::const_iterator lit = contours.begin(); lit != contours.end(); ++lit)
    {
        Line l;

        // get centriod
        long long x_sum, y_sum;
        x_sum = y_sum = 0;
        for(vector<Point>::const_iterator pit = lit->begin(); pit != lit->end(); ++pit)
        {
            x_sum += pit->x;
            y_sum += pit->y;
        }
        int x = x_sum/lit->size();
        int y = y_sum/lit->size();
        l.centriod = Point(x, y);

        // get points number
        l.n = lit->size();

        // get average grey
        unsigned long long grey_sum = 0;
        for (vector<Point>::const_iterator pit = lit->begin(); pit != lit->end(); ++pit)
        {
            grey_sum += orig_m.at<uchar>(*pit); 
        }
        l.grey = grey_sum/l.n;

        // get vertex
        RotatedRect rect = minAreaRect(Mat(*lit));

        // only save the up-right rectangles.
        if (abs(rect.angle) == 0 or abs(rect.angle) == 90 or abs(rect.angle) == 180 or abs(rect.angle) == 270)
        {

            Point2f verticals[4] ;
            rect.points(verticals);
            l.vertex = verticals[2];

            double w = line_length(verticals[0], verticals[1]);
            double h = line_length(verticals[2], verticals[1]);
            if (w > m.cols/5 or h > m.rows/5 or w < 5 or h < 5)
            {
                continue; 
            }
            if (w/h >7 or h/w >7)
            {
                continue;
            }
            l.width= w;
            l.height = h;

            l.grey = get_average_grey(orig_m, verticals[2], w, h);

            rectangle(orig_m, rect.boundingRect(), Scalar(0,0,0));
#if 0
            for (int i=0; i < 4; i++)
            {
                line(orig_m, verticals[i], verticals[(i+1)%4], Scalar(0,0,0));
            }

#endif
            lchains.insert(make_pair(l, *lit));
        }
    }
#if 1
    showimage("oooo", orig_m);
    showimage("mmmm", m);
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


    map<Line, vector<Point> > lchains;
    Mat dst;
    //Canny(image, dst, 40, 120, 3);
    Canny(image, dst, 50, 150, 3);
    Mat tm;
    threshold(dst, tm, 0, 255, THRESH_BINARY| THRESH_OTSU);
    get_line(image, tm, lchains);

    print_lchains(lchains);

    return 0;
}			/* ----------  end of function main  ---------- */

