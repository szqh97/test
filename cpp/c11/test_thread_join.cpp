#include <iostream>
#include <thread>
#include <cstdlib>
#include <unistd.h>
using namespace std;
void func() 
{
    sleep(3);
    cout << "ttttt" << endl;
}

void func2()
{
    sleep(3);
    cout << "ssssssss" << endl;
}

int main ( int argc, char *argv[] )
{
    std::thread t(func);
    //t.join();
    
    std::thread t2 (func2);
    //t2.join();
    cout << "aaaaaaaaaaa" << endl;
    return 0;
}			/* ----------  end of function main  ---------- */
