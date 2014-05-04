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

float line_length(const Point2f &p1, const Point2f &p2)
{

    cout << " __________ " << p1 << " " << p2 << endl;
    double dx = p1.x - p2.x ;
    double dy = p1.y - p2.y;
    return sqrt(dx*dx + dy*dy);
}
int main ( int argc, char *argv[] )
{
    Point2f p1(110, 239),  p2(110, 226);
    cout << line_length(p1, p2) << endl;
    return 0;
}			/* ----------  end of function main  ---------- */

