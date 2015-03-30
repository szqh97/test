#include <iostream>
using namespace std;
struct Test{
    Test(){}
    virtual ~Test(){}
    int num;
    void func(){cout << "mem functions" << endl;}
};

int Test::*ptr_num = &Test::num;

void (Test::*ptr_func)() = &Test::func;

int main ( int argc, char *argv[] )
{
    Test t;
    Test *pt = new Test;

    (t.*ptr_func)();
    (pt->*ptr_func)();

    t.*ptr_num = 1;
    pt->*ptr_num = 2;
    delete pt;
    return 0;
}			/* ----------  end of function main  ---------- */

