#include <iostream>
#include <thread>
#include <assert.h>
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

struct func;

void daemon_sleep()
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }
}

void oop(){
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
    std::cout << some_local_state << std::endl;
}

class X{
public:
    void do_length_work(){
        std::cout << "X::do_length_work" << std::endl;
    }
};

X my_x;

void class_method(){
    std::thread t(&X::do_length_work, &my_x);
    t.join();
}
int main()
{
    std::thread t(daemon_sleep);
    t.detach();
    assert(!t.joinable());
    class_method();
    return 0;
}
