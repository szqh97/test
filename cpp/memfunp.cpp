#include <iostream>
using namespace std;

class P
{
public:
    void print()
    {
        cout << "p::print()" << endl;
    }

};

typedef void (P::*fun)();

int main ( int argc, char *argv[] )
{
    fun f;
    P tmp;
    f = &P::print;
    (tmp.*f)();

    


    return 0;
}			/* ----------  end of function main  ---------- */
