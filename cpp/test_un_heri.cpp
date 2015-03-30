#include <iostream>

using namespace std;
class AbstractFinal
{
    protected:
        AbstractFinal(){}
        ~AbstractFinal(){}
};
class FinalClass: virtual private AbstractFinal {};

class Child : public FinalClass {};
int main ( int argc, char *argv[] )
{

//    Child c;
    AbstractFinal a;
    return 0;
}			/* ----------  end of function main  ---------- */
