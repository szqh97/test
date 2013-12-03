#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;


int main ( int argc, char *argv[] )
{
    FILE *fp = fopen("./aaaaa", "w");
    int i = 344;
    stringstream ss;
    ss<<i;

    string s = "<shot>";
    s+= ss.str();
    s+= "</shot>\n<shot>";
    ss << 789;
    s += ss.str(); 

    cout << s << endl;

    fwrite(s.c_str(), s.size(), 1, fp);
    fclose(fp);
    return 0;
}			/* ----------  end of function main  ---------- */
