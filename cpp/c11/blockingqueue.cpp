#include <mutex>
#include <queue>
#include <thread>
#include <assert.h>
#include <iostream>
#include <condition_variable>

std::mutex mutex_;
//std::unique_lock<std::mutex> lock(mutex_);
std::condition_variable cv;
std::deque<int> queu;
int dequeue()
{
    std::unique_lock<std::mutex> lock(mutex_);
    while(queu.empty())
    {
        cv.wait(lock);
    }

    assert(!queu.empty());
    int top = queu.front();
    queu.pop_front();
    return top;

}

void enqueue(int x)
{
        std::unique_lock<std::mutex> lock(mutex_);
        size_t n = queu.size();
        queu.push_back(x);
        cv.notify_one();
}

void func1()
{

    for (int i = 0; i < 100; ++i)
    {
        enqueue(i);
        std::cout << "in enqueue .." << std::endl;
    }

}


void func2()
{
    for(int i = 0; i< 100; ++i)
    {
        std::cout << dequeue() << std::endl;
    }

}
int main ( int argc, char *argv[] )
{

    std::vector<std::thread> threads;
    for (int i = 0; i < 30; ++i)
    {
        threads.push_back(std::thread(func1));
    }
    for (int i = 0; i < 10; ++i)
    {
        threads.push_back(std::thread(func2));
    }

    for(std::vector<std::thread>::iterator it = threads.begin(); it != threads.end(); ++it)
    {
        (*it).join();
    }

    while (1)
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
    return 0;
}			/* ----------  end of function main  ---------- */

