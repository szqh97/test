#include <boost/timer.hpp>
#include <iostream>
using namespace boost;
using namespace std;

int main ( int argc, char *argv[] )
{
    timer t;
    cout << "max timespan: " << t.elapsed_max() << endl;
    cout << "min timespan: " << t.elapsed_min() << endl;
    cout << "now time elapsed: " << t.elapsed() << "s" << endl;

    return 0;
}			/* ----------  end of function main  ---------- */

