#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
using namespace cv;
class Line{
    public:
        Point2f centriod;
        Point2f vertex;
        double width;
        double height;
        unsigned int n;
        double grey;
        friend bool operator < (const Line &ls, const Line &rs);
        friend bool operator == (const Line &ls, const Line &rs);

};
inline bool operator < (const Line &ls, const Line &rs)
{
    return ((ls.vertex.x < rs.vertex.x and ls.vertex.y < rs.vertex.y)
            or (ls.width*ls.height < rs.width * rs.height)
            or (ls.n < rs.n )
            or (ls.grey < rs.grey)
        );
}

inline bool operator == (const Line &ls, const Line &rs)
{
    return ls.vertex.x == rs.vertex.x and ls.vertex.y == rs.vertex.y 
        and ls.centriod.x == rs.centriod.x and ls.centriod.y == rs.centriod.y
        and ls.width == rs.width 
        and ls.height == rs.height
        and ls.grey == rs.grey
        and ls.n == rs.n;
}

double min(double d1, double d2)
{
    return d1 < d2 ? d1 : d2;
}
 
double max(double d1, double d2)
{
    return d1 > d2 ? d1 : d2;
}

void showimage(const char *t, Mat& m)
{
#define SHOW 1
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

double get_average_grey(Mat &orgin_m, const Rect &roi)
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

//void get_line(Mat &orig_m, Mat &m, map<Line, vector<Point> > &lchains)
void get_line(const char* fname, Mat &orig_m, Mat &m, map<Line, vector<Point> > &lchains)
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
        bool allinside = true;
        int roi_x = 95, roi_y = 305;
        int roi_w = 350, roi_h = 35;
        Rect text_roi(roi_x*2.3, roi_y*2.3, roi_w*2.3, roi_h*2.3);
        for(vector<Point>::const_iterator pit = lit->begin(); pit != lit->end(); ++pit)
        {
            x_sum += pit->x;
            y_sum += pit->y;
            if ((*pit).inside(text_roi))
            {
                allinside = false;
            }
            
        }
        /* 

        if (allinside)
        {
            continue;
        }
        */
        
        int x = x_sum/lit->size();
        int y = y_sum/lit->size();
        l.centriod = Point(x, y);

        // get points number
        l.n = lit->size();

        // get vertex
        RotatedRect rect = minAreaRect(Mat(*lit));

        // only save the up-right rectangles.
        //if (abs(rect.angle ) < 10 or abs(rect.angle -90) < 10 or abs(rect.angle - 180) < 10 or abs(rect.angle - 270) < 10)
        if (1)
        {

            Point2f verticals[4] ;
            rect.points(verticals);
            l.vertex = verticals[2];

            double w = line_length(verticals[0], verticals[1]);
            double h = line_length(verticals[2], verticals[1]);
            //if (w > roi_w/4 or h > roi_h/2 or w < 7 or h < 7)
            if (w > 50 or h > 50 or w < 7 or h < 7)
            {
                continue; 
            }
            if (w/h >5 or h/w >5)
            {
                continue;
            }
            l.width= w;
            l.height = h;

            // get average grey
            //l.grey = get_average_grey(orig_m, rect.boundingRect());

#if 1
            for (int i=0; i < 4; i++)
            {
                line(orig_m, verticals[i], verticals[(i+1)%4], Scalar(0,0,0));
            }
#endif
        //        rectangle(orig_m, rect.boundingRect(), Scalar(0,0,0));
                //rectangle(orig_m, rect.boundingRect(), Scalar(255, 255, 255));
                lchains.insert(make_pair(l, *lit));
        }
    }
#if 1
    char new_name[100];
    sprintf(new_name, "%s.png", fname);
    imwrite(new_name, orig_m);
    showimage("oooo", orig_m);
    showimage("mmmm", m);
#endif

}


//int gen_text_Region(map<Line, vector<Point> > &lchains, map<double, vector<Point> > &lchain)
int gen_text_Region(map<Line, vector<Point> > &lchains)
{
    int i = 0;
    for (map<Line, vector<Point> >::iterator mlit = lchains.begin();
            mlit != lchains.end(); ++mlit)
    {
        Line li = mlit->first;
        map<Line, vector<Point> >::iterator it = mlit;
        for (++it; it != lchains.end(); ++it)
        {
            ++i;
            Line lj = it->first;
            double dx = li.centriod.x - lj.centriod.x;
            double dy = li.centriod.y - lj.centriod.y;
            double d_corr = sqrt(dx * dx + dy * dy) / sqrt(li.width * li.height + lj.width * lj.height);
            double s_corr = 1 - min(li.width/li.height, lj.width/lj.height) / max(li.width/li.height, lj.width/lj.height);
            double a_corr = 1 - min(li.width*li.height, lj.width*lj.height) / max(li.width*li.height, lj.width*lj.height);
            double grey_corr = abs(li.grey -lj.grey);
            //cout << "m_corr: " <<d_corr << ", " << s_corr << ", " << a_corr << ", " << grey_corr << endl;


        }
    }
    cout << "cccccccccccccc " << i << endl;
    cout << lchains.size() << endl;
    return 0;
}

int main ( int argc, char *argv[] )
{
    Mat image;
    if (argc != 2 ) {
        cout << argc << "no image data\n";
        return -1;
    }
    image = imread(argv[1], 0);
    Mat blurred;
    double sigma=1;
    GaussianBlur(image, blurred, Size(1,1), sigma, sigma);
    //blur(image, blurred, 

    Size dsize = Size(blurred.cols * 2.3 , blurred.rows * 2.3);
    Mat resized;
    resized = Mat(dsize, blurred.type());
    resize(blurred, resized, dsize, 0, 0, INTER_CUBIC);


    map<Line, vector<Point> > lchains;
    Mat dst;
    Canny(resized, dst, 40, 120, 3);
    showimage("resized", resized);
    showimage("canny", dst);
    //get_line(image, tm, lchains);
    get_line(argv[1], resized, dst, lchains);
    gen_text_Region(lchains);

    print_lchains(lchains);

    return 0;
}			/* ----------  end of function main  ---------- */
#if 0
int main ( int argc, char *argv[] )
{
    Mat image;
    if (argc != 2 ) {
        cout << argc << "no image data\n";
        return -1;
    }
    image = imread(argv[1], 0);
    Mat blurred;
    double sigma=1;
    GaussianBlur(image, blurred, Size(), sigma, sigma);


    map<Line, vector<Point> > lchains;
    Mat dst;
    Canny(image, dst, 40, 120, 3);
    //Canny(blurred, dst, 50, 150, 3);
    Mat tm;
    threshold(dst, tm, 0, 255, THRESH_BINARY| THRESH_OTSU);
    //get_line(image, tm, lchains);
    get_line(argv[1], image, dst, lchains);
    gen_text_Region(lchains);

    print_lchains(lchains);

    return 0;
}			/* ----------  end of function main  ---------- */
#endif

