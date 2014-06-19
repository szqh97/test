#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <map>
using namespace std;

int f()
{
    int x;
    cout << x << (int)1&&x << endl;
    return x==(1&&x);
}
int main ( int argc, char *argv[] )
{

    cout << f() << endl;
    return 0;
}			/* ----------  end of function main  ---------- */

