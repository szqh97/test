#include<iostream>
#include <thread>
#include <string>
#include <mutex>

class some_data
{
public:
    void do_something()
    {
        return;
    }
private:
    int a;
    std::string b;
};

class data_wrapper
{
public:
    template<typename Function>
        void process_data(Function func)
        {
            std::lock_guard<std::mutex> l(m);
            func(data); // 1
        }
private:
    some_data data;
    std::mutex m;
};

some_data* unprotected;
void malicious_function(some_data& unprotected_data)
{
    unprotected = &unprotected_data;
}

data_wrapper x;
void foo()
{
    x.process_data(malicious_function); //2
    unprotected->do_something(); //3
}
