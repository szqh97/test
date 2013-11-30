#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;


int main ( int argc, char *argv[] )
{
    string videofilename;
    ifstream vfile("t.out");
    while (vfile >> videofilename)
    {
        cout << videofilename << endl;

    }

    long long int t = 12345;
    char name[100];
    sprintf(name, "%06lld",(t/1000));
    cout << name << endl;
    return 0;
}			/* ----------  end of function main  ---------- */
