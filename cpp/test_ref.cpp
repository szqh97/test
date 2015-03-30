#include <iostream>
using namespace std;
struct Foo{
    void foo() & {cout << "lvalue" << endl;}
    void foo() && {cout << "rvalue" << endl;}
};

int main ( int argc, char *argv[] )
{
    Foo f;
    f.foo();
    Foo().foo();
    return 0;
}	

