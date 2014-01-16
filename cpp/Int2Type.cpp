#include <iostream>
using namespace std;

template <int v>
struct Int2Type
{
    enum { value = v};
};


int main ( int argc, char *argv[] )
{
    Int2Type<0> I0;
    return 0;
}			/* ----------  end of function main  ---------- */

