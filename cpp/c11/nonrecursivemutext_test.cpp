#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;
mutex m;
class Foo
{
    public:
        void doit()
        {
            std::cout << "just doit " << std::endl;
        }
};

vector<Foo> foos;
void post(const Foo& f)
{
    std::lock_guard<std::mutex> lock(m);
    foos.push_back(f);
}

void traverse()
{
    std::lock_guard<std::mutex> lock(m);
    for(vector<Foo>::iterator it = foos.begin(); it != foos.end(); ++it)
    {
        it->doit();
    }
}


void func1()
{
    // test dead lock
    //std::lock_guard<std::mutex> lock(m);
    std::cout << "the thread id is " << std::this_thread::get_id() << std::endl;
    for (auto i = 0; i < 100; ++i)
    {
        Foo f;
        post(f);
    }
    traverse();
}

int main ( int argc, char *argv[] )
{

    for(auto i = 0; i < 10; ++i)
    {
        std::thread t(func1);
        t.join();
    }

    return 0;
}			/* ----------  end of function main  ---------- */

