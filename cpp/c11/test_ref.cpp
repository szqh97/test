#include <iostream>
#include <thread>

using namespace std;

void func(int& a)
{
    ++a;
}
void f()
{
    cout << "ttttt" << endl;
}


int main ( int argc, char *argv[] )
{
    int a = 43;
    std::thread t(func, std::ref(a));
    std::thread t2(f);
    t.swap(t2);
    t.join();
    t2.join();
    cout << "a is: " << a << endl;
    return 0;
}			/* ----------  end of function main  ---------- */

