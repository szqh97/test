#include <iostream>
#include <memory>

using namespace std;
struct Foo
{
    Foo(){cout << "Foo::Foo\n";}
    ~Foo(){ cout << "Foo::~Foo\n"; }
    void bar() {cout << "Foo::bar\n";}
};
void f(const Foo &)
{
    cout << "f(const Foo&) \n";
}

int main ( int argc, char *argv[] )
{

    unique_ptr<Foo> p1(new Foo);
    if (p1) p1->bar();
    {
        unique_ptr<Foo>p2(move(p1));
        if (p1 == nullptr) cout << "p1 is null \n";
        f(*p2);
        p1 = move(p2);
        cout << "desroying p2...\n";
        
    }
    if (p1) p1->bar();
    return 0;
}			/* ----------  end of function main  ---------- */

