#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

int g_num = 0;
std::mutex g_mutex;

class Mutex
{
public:
    Mutex(){gm.lock();}
    ~Mutex(){gm.unlock();}
private:
    mutex gm;
};

void thread1()
{
    //g_mutex.lock();
    
    Mutex m;
    g_num = 10;
    for (int i = 0; i < 10; ++i)
    {
        cout << "thread 1 : " << g_num << endl;
    }
    //g_mutex.unlock();
}

void thread2() 
{
    //g_mutex.lock();
    Mutex m;
    g_num = 20;
    for (int i = 0; i < 10; ++i)
    {
        cout << "thread 2 : " << g_num << endl;
    }
    //g_mutex.unlock();
}


int main ( int argc, char *argv[] )
{
    thread t1(thread1);
    thread t2(thread2);
    t1.join();
    t2.join();
    return 0;
}			/* ----------  end of function main  ---------- */
