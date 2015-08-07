#include <iostream>
#include <thread>

using namespace std;

void thread_func()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main ( int argc, char *argv[] )
{
    int i = 0;
    for (;i < 65535; ++i)
    {
        thread t(thread_func);
        //t.join();
        t.detach();
        cout << i << endl;
    }
    return 0;
}			/* ----------  end of function main  ---------- */
