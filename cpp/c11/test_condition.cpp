#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

using namespace std;

class Foo
{
    public:
        Foo () : flag_(0)
               , thread1_(std::bind(&Foo::threadFunc1, this))
               , thread2_(std::bind(&Foo::threadFunc2, this)){}
        ~Foo() 
        {
            thread1_.join();
            thread2_.join();
        }
    private:
        void threadFunc1()
        {
            {
                std::unique_lock<mutex> ul(mutex_);
                while (0 == flag_)
                {
                    cond_.wait(ul);
                }
                cout << flag_ <<endl;
            }
        }
        void threadFunc2()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            std::unique_lock<std::mutex> ul(mutex_);
            flag_ = 100;
            cond_.notify_one();
        }
        int flag_;
        mutex mutex_;
        condition_variable cond_;
        thread thread1_;
        thread thread2_;
}; 


int main ( int argc, char *argv[] )
{
    Foo f;
    return 0;
}			/* ----------  end of function main  ---------- */
