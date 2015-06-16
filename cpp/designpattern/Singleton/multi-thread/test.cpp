#include "Singleton.h"
#include <thread>
#include <memory>
#include <iostream>


class Foo
{
    public:
        void fun()
        {
            std::cout << "in Foo::func(), and this is : " << static_cast<void*> (this) << std::endl;
        }

        int i;

};
void ThreadFunc()
{

    Foo* f = new Foo();
    std::cout << "Foo is : " << static_cast<void*>(f) << std::endl;

    Foo& pf1 = PthreadVersion::Singleton<Foo>::instance();
    std::cout << "in Singleton, pf is: " << static_cast<void*> (&pf1) << std::endl;
    pf1.i = 8;

    std::shared_ptr<Foo> spf =SingletonSharedPtr::Singleton<Foo>::instance();
    //std:: cout << "Singleton by shared_ptr: " << SingletonSharedPtr::Singleton<Foo>::instance().get()<< std::endl;
    std::cout << "Singleton, spf is: " << static_cast<void*>(spf.get())<< std::endl;
    spf->i = 88;
    if (!spf)
        std::cout << "upf is null?" <<std::endl;
}
void printI()
{
    std::shared_ptr<Foo> spf =SingletonSharedPtr::Singleton<Foo>::instance();
    std::cout <<"==== the end, i is: " << spf->i << std::endl;
 
}

int main ( int argc, char *argv[] )
{

    for (int i = 0; i < 10; i++)
    {
        std::thread t(ThreadFunc);
        t.join();

    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::thread tt(printI);
    tt.join();


    return 0;
}			/* ----------  end of function main  ---------- */

