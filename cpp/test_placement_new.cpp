#include <iostream>
#include <cstdlib>
using namespace std;
struct Test {
    int data;
    Test() {data = 22;cout << "Test::Test()" << endl;}
    ~Test() {cout << "Test::~Test()" << endl;}
};

int main ( int argc, char *argv[] )
{
    Test *ptr = (Test*)malloc(sizeof(Test));
    new (ptr) Test;
    cout << ptr->data << endl;
    ptr->~Test();
    free(ptr);
    return 0;
}			/* ----------  end of function main  ---------- */

