#include <iostream>
#include <string>
using namespace std;


int bar(int(x));
string foo(string());
string test()
{
    return "test";
}


int main ( int argc, char *argv[] )
{
    cout << bar(2) << endl;
    cout << foo(test) << endl;

    return 0;
}			/* ----------  end of function main  ---------- */

int bar(int(x)) 
{
    return 2;
}

string foo(string(*fun)())

{
    return (*fun)();
}

