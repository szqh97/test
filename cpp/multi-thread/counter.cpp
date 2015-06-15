// A thread-safe conuter
#include <boost/core/noncopyable.hpp>
#include <atomic>
#include <thread>
#include <mutex>
#include <iostream>
using namespace std;
std::mutex m_;
class Counter : boost::noncopyable
{
public:
    Counter(): _v(0) { }


    int64_t value() const;
    int64_t getAndIncrease();
private:
    atomic<long> _v;

};

int64_t Counter::value() const
{
    std::lock_guard<std::mutex> g_lock(m_);
    return _v;

}

int64_t Counter::getAndIncrease()
{

    std::lock_guard<std::mutex> g_lock(m_);
    int64_t ret = ++_v;
    return ret;
}



int main ( int argc, char *argv[] )
{

    Counter c;
    int64_t i = c.getAndIncrease();
    i = c.getAndIncrease();
    cout << i << endl;
    

    return 0;
}			/* ----------  end of function main  ---------- */
