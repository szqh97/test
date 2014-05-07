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
        Point2f verticals[4];
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

void print_hist(const vector<int> &hist)
{
    for (int i = 0; i < hist.size(); ++i)
    {
        cout << i << ": "<< hist[i] << endl;
    }
}
void print_lchains(const vector<Line> &lines)
{
    cout << "sssss" << endl;
    //for (map<Line, vector<Point> >::const_iterator it = lines.begin(); it != lines.end(); ++it)
    for(vector<Line>::const_iterator it = lines.begin(); it != lines.end(); ++it)
    {
        Line l = *it;
        cout << "centriod: " << l.centriod << " "
            << "vertex: " << l.vertex << " "
            << "width: " << l.width << " "
            << "height: " << l.height << " "
            << "n: "<< l.n << " "
            << "grey: " << l.grey << " "
            << "verticals: " <<l.verticals[0] << ", " 
            << l.verticals[1] << ", " 
            << l.verticals[2] << ", "
            << l.verticals[3] << endl;
    }
}

double line_length(const Point2f &p1, const Point2f &p2)
{

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

/*
 * function pro = kx-y+j, take two points a and b.
 * compute the line argument k and j, then return the  pro value
 * so that can be used to detemine whether the point p is on the left or right 
 * of the line ab
 */
double computeProduct(Point &p, Point2f &a, Point2f &b)
{
    double k = (a.y-b.y)/(a.x-b.x);
    double j = a.y-k*a.x;
    return k*p.x - p.y + j;
}

/*
 * decide whether point p is in the ROI.
 * The ROI is a rotated rectangle whose 4 conrners are stored in roi[]
 */
bool isInROI(Point &p, Point2f roi[])
{
    double pro[4];
    for (int i = 0; i < 4; ++i)
    {
        pro[i] = computeProduct(p, roi[i], roi[(i+1)%4]);
    }
    if (pro[0] * pro[2] < 0 and pro[1] * pro[3] < 0)
    {
        return true;
    }
    return false;
}


//void get_line(Mat &orig_m, Mat &m, map<Line, vector<Point> > &lchains)
//void get_line(const char* fname, Mat &orig_m, Mat &m, map<Line, vector<Point> > &lchains)
void get_line(const char* fname, Mat &orig_m, Mat &m, vector<Line> &lchains)
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
            memcpy(l.verticals, verticals, sizeof(Point2f)*4);
            l.vertex = verticals[2];

            double w = line_length(verticals[0], verticals[1]);
            double h = line_length(verticals[2], verticals[1]);
            //if (w > roi_w/4 or h > roi_h/2 or w < 7 or h < 7)
            //if (w > 50 or h > 50 or w < 7 or h < 7)
            //if (w > m.cols/4 or h > m.rows/2 or w < 7 or h < 7)
            //if (w > m.cols/4 or h > m.rows/2 or w < 7 or h < 7)
            if (w > 4*20*2.3 or h > 30*2.3 or w < 7 or h < 7)
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
                line(orig_m, verticals[i], verticals[(i+1)%4], Scalar(255,255,255));
                //line(orig_m, verticals[i], verticals[(i+1)%4], Scalar(0,0,0));
            }
#endif
            lchains.push_back(l);
        }
    }
#if 1
    char new_name[100];
    sprintf(new_name, "%s.png", fname);
    imwrite(new_name, orig_m);
#endif

}

void get_hist_h(const Mat& m, const Rect &rect, vector<Line>&lchains, vector<int> &hist_h)
{
    for (int r = 0; r < m.rows; ++r)
    {
        for (int c = 0; c < m.cols; ++c)
        {

            Point p(c, r);
            if (p.inside(rect) and (int)m.at<uchar>(r,c) > 0)
            {
                for (vector<Line>::const_iterator lit = lchains.begin(); 
                        lit != lchains.end(); ++lit)
                {
                    if (isInROI(p, (Point2f*)lit->verticals))
                    {
                        ++hist_h[r];
                    }

                }
            }
        }
    }
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
    //blur(image, blurred, 

    Size dsize = Size(image.cols * 2.3 ,image.rows * 2.3);
    Mat resized;
    resized = Mat(dsize, image.type());
    resize(image, resized, dsize, 0, 0, INTER_CUBIC);


    vector<Line> lchains;
    Mat dst;
    GaussianBlur(resized, blurred, Size(5,5), 0, 0);
    Mat b;
    threshold( blurred, b, 0, 255, THRESH_OTSU|THRESH_BINARY);
    Mat opened;
    Mat element(3,3,CV_8U, cv::Scalar::all(255));
    morphologyEx(b, opened, MORPH_OPEN, element);
    Canny(opened, dst, 40, 120, 5);
    //get_line(image, tm, lchains);

      
    Mat dd, dd2; 
    dst.copyTo(dd);
    dst.copyTo(dd2);
    get_line(argv[1],dd, dst, lchains);

    vector<int> hist_h(dd.rows, 0);

    int roi_x = 95, roi_y = 305;
    int roi_w = 350, roi_h = 35;
    Rect text_roi(roi_x*2.3, roi_y*2.3, roi_w*2.3, roi_h*2.3);
    get_hist_h(dd2, text_roi, lchains, hist_h);
    //gen_text_Region(lchains);

    showimage("dd2", dd2);
    //print_lchains(lchains);
    print_hist(hist_h);

    return 0;
}			/* ----------  end of function main  ---------- */
