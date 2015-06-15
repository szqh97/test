#include <iostream>
#include <thread>
#include <string>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
void my_thread(int num, const string& str)
{
    system("sleep 2");
    cout << "num: " << num << ", name: " << str << endl;
}

void func()
{
    system("sleep 2");
    cout << "thread func" << endl;
}

int main ( int argc, char *argv[] )
{
    int num = 1234;
    string str = "testst";
    thread t(my_thread, num, str);
    t.detach();

    thread t1(func);
    t1.detach();
    cout << "in main thread " << endl;

    while(1)
    {
    cout << "in main thread ..." << endl;
       system("sleep 1") ;
    }

    return 0;
}			/* ----------  end of function main  ---------- */

