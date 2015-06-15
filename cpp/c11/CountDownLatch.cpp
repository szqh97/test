#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <boost/noncopyable.hpp>

class CountDownLatch: boost::noncopyable
{
    public:
       explicit CountDownLatch(int count): cv_(), count_(0){}
        void wait();
        void countDown();
        int get_count() const;
    private:
        static std::mutex mutex_;
        std::condition_variable cv_;
        int count_;
};


//std::mutex CountDownLatch::mutex_ = std::mutex();

void CountDownLatch::wait()
{
    std::unique_lock<std::mutex> lock(mutex_);
    while (count_ > 0)
    {
        cv_.wait(lock);
    }
}

int CountDownLatch::get_count() const
{
    std::unique_lock<std::mutex> lock(mutex_);
    return count_;
}
void CountDownLatch::countDown()
{
    std::unique_lock<std::mutex> lock(mutex_);
    --count_;
    if (count_ == 0)
    {
        cv_.notify_all();
    }
}



int main ( int argc, char *argv[] )
{
    
    return 0;
}			/* ----------  end of function main  ---------- */
