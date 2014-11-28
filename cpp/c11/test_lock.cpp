#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <mutex>

using namespace std;
timed_mutex g_timed_mutex;

void thread1()
{
    unique_lock<timed_mutex> t1 (g_timed_mutex);
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "thread1" << endl;
}

void thread2()
{
    unique_lock<timed_mutex> t1(g_timed_mutex, chrono::milliseconds(30000));
    cout << "thread2" << endl;

}

int main ( int argc, char *argv[] )
{
    thread t1(thread1);
    //this_thread::sleep_for(chrono::milliseconds(10000));
    thread t2(thread2);
    t1.join();
    t2.join();
    return 0;
}			/* ----------  end of function main  ---------- */

