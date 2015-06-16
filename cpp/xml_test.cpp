#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int main ( int argc, char *argv[] )
{
    char *file = "./test.xml";
    string info = "<shots>\n</shots>\n";
    FILE *fp = fopen(file, "w");
    fwrite(info.c_str(), info.size(), 1, fp);
    fflush(fp);
    string t = "<shots>\n";
    fseek(fp, t.size(), SEEK_SET);
    fwrite("abcde", 5, 1, fp);
    fflush(fp);
    fclose(fp);
        

    return 0;
}			/* ----------  end of function main  ---------- */

