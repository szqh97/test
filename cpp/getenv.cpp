#include <iostream>
#include <stdlib.h>
using namespace std;

int main ( int argc, char *argv[] )
{
    cout << getenv("CLOSE_EDGE_DETECT") << endl;
    sleep(10);
    cout << getenv("CLOSE_EDGE_DETECT") << endl;
    sleep(10);
    cout << getenv("CLOSE_EDGE_DETECT") << endl;
    return 0;
}			/* ----------  end of function main  ---------- */

