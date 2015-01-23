#include <boost/progress.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
using namespace std;
using namespace boost;

int main ( int argc, char *argv[] )
{
    vector<string> v(10, "aaa");
    v[1] = ""; v[3] = "";
    ofstream fs("test.txt");
    progress_display pd(v.size());
    vector<string>::iterator pos;
    for (pos = v.begin(); pos != v.end(); ++pos)
    {
        fs << *pos << endl;
        ++pd;
        if (pos->empty())
        {
            cout << "null string # " << (pos - v.begin()) << endl;
        }
    }
    return 0;
}			/* ----------  end of function main  ---------- */


