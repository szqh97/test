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

typedef std::function<void()> Task;
class ThreadPool
{
    public:
        ThreadPool (int );
        ~ThreadPool ();
        ThreadPool(const ThreadPool&) = delete;
        void operator=(const ThreadPool&) = delete;
        void setMaxQueueSize(int maxsize);
        void start();
        void stop();
        void run(const Task& t);

    private:
        bool isFull() const;
        void threadFunc();
        Task take();

    private:
        int num_;
        std::mutex mutex_;
        std::condition_variable notEmpty_;
        std::condition_variable notFull_;
        std::vector<std::thread> threads_;
        std::deque<Task> queue_;
        size_t maxQueueSize_;
        bool running_;
};
