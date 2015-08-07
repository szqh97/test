 #include <iostream>
#include <thread>
#include <cstdlib>
#include <unistd.h>
using namespace std;
void f()
{
    char *p = new char[1024];
    cout << "new char ..." << endl;
    delete []p;
}

int main ( int argc, char *argv[] )
{
    std::thread t(f);
    cout << t.get_id() << endl;
    t.detach();
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << "int main thread..." << endl;
    thread::id id1 = thread::id();

    thread::id id2 = thread::id();
    if (id1 == id2) 
    {
        cout << "xxxxxxxxxxx" << endl;
    }
    cout << std::this_thread::get_id() << endl;



    return 0;
}			/* ----------  end of function main  ---------- */
