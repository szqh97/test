#include <iostream>
#include <thread>

struct func {
    int& m;
    func(int& i_): m(i_){}
    void operator()()
    {
        for (int i = 0; i < 1000; ++i) {
            ++m;
        }
    }
};

class thread_guard
{
public:
    explicit thread_guard(std::thread& t_):
        t(t_){}
    ~thread_guard()
    {
        if (t.joinable())
        {
            t.join();
        }
    }
    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete;

private:
    std::thread& t;
};


