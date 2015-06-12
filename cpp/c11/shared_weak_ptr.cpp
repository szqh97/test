#include <iostream>
#include <memory>
using namespace std;

struct Linker
{
    weak_ptr<Linker> link;
//    shared_ptr<Linker> link; // error while use shared_ptr, 
};

void Dowork()
{
    shared_ptr<Linker> l1(new Linker());
    shared_ptr<Linker> l2(new Linker());
    l1->link = l2;
    l2->link = l1;
}
int main ( int argc, char *argv[] )
{
    Dowork();
    return 0;
}			/* ----------  end of function main  ---------- */

