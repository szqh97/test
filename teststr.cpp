#include <string.h>
#include <iostream>
using namespace std;


int main ( int argc, char *argv[] )
{
    char s1[512];
    strcpy(s1, "2.1234545463405.a.mp4");
    cout << s1 << endl;
    cout << strstr(s1, "a.mp4") << endl;

    return 0;
}			/* ----------  end of function main  ---------- */

