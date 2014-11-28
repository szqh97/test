#include <iostream>
#include <thread>
#include <functional>
#include <string>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <vector>
#include <assert.h>
#include <queue>

class ThreadPool
{
    public:
        typedef std::function<void()> Task;

        ThreadPool (int num)
            :num_(num)
            , maxQueueSize_(0)
            , running_(false){}

        ~ThreadPool ()
        {
            if (running_)
            {
                stop();
            }
        }                       

        ThreadPool(const ThreadPool&) = delete;
        void operator=(const ThreadPool&) = delete;

        void setMaxQueueSize(int maxsize)
        {
            maxQueueSize_ = maxsize;
        }

        void start()
        {
            assert(threads_.empty());
            running_ = true;
            threads_.reserve(num_);
            for (auto i = 0; i < num_; ++i)
            {
                threads_.push_back(std::thread(std::bind(&ThreadPool::threadFunc, this)));
            }

        }

        void stop()
        {
            {
                std::unique_lock<std::mutex> ul(mutex_);
                running_ = false;
                notEmpty_.notify_all();
            }

            for (auto &iter : threads_)
            {
                iter.join();
            }

        }

        void run(const Task& t) 
        {
            if (threads_.empty())
            {
                t();
            }
            else
            {
                std::unique_lock<std::mutex> ul(mutex_);
                while (isFull())
                {
                    notFull_.wait(ul);
                }
                assert(!isFull());
                queue_.push_back(t);
                notEmpty_.notify_one();
            }
        }

    private:
        bool isFull() const
        {
            return maxQueueSize_ > 0 and queue_.size() > maxQueueSize_;
        }
        
        void threadFunc()
        {
            std::cout << "crate id " << std::this_thread::get_id() << std::endl;
            while (running_)
            {
                Task task(take());
                //Task task(take());
                if (task)
                {
                    task();
                }
            }
            std::cout << "thread id: " << std::this_thread::get_id() <<std::endl;
        }

        Task take()
        {
            std::unique_lock<std::mutex> ul(mutex_);
            while (queue_.empty() and running_)
            {
                notEmpty_.wait(ul);
            }
            Task task;
            if (!queue_.empty())
            {
                task = queue_.front();
                queue_.pop_front();
                if (maxQueueSize_ > 0)
                {
                    notFull_.notify_one();
                }
            }
            return task;
        }

        int num_;
        std::mutex mutex_;
        std::condition_variable notEmpty_;
        std::condition_variable notFull_;
        std::vector<std::thread> threads_;
        std::deque<Task> queue_;
        size_t maxQueueSize_;
        bool running_;
};

void fun() {
    std::cout << "<id: " << std::this_thread::get_id() << " > hello world!" << std::endl;
}

int main ( int argc, char *argv[] )
{
    {
        std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;
        ThreadPool pool(3);
        pool.setMaxQueueSize(100);
        pool.start();
        for (auto i = 0; i < 1000; i++)
        {
            pool.run(fun);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
    return 0;
}
