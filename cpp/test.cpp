#include <iostream>
#include <vector>

typedef int UINT4;
using namespace std;
class Hack
{
};

Hack& operator< (Hack &a , Hack &b)
{
    std::cerr << "小于操作符\n";
    return a;
}

Hack& operator> (Hack &a, Hack &b)
{
    std::cerr <<  "大于操作符\n";
    return a;
}

int main(int argc, char ** argv)
{
    Hack vector;
    Hack UINT4;
    Hack foo;

//    vector<UINT4> foo;
}
