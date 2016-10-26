#include <iostream>
#include <thread>
#include <numeric>
#include <functional>

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

class scrop_thread
{
public:
    explicit scrop_thread(std::thread t_):
        t(std::move(t_))
    {
        if (!t.joinable()) {
            throw std::logic_error("No thread");
        }
    }
    ~scrop_thread()
    {
        t.join();
    }
    scrop_thread(scrop_thread const&)=delete;
    scrop_thread& operator=(scrop_thread const&)=delete;
private:
    std::thread t;
};


template <typename Iterator, typename T>
struct accumulate_block {
    void operator()(Iterator first, Iterator last, T& result){
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init){
    unsigned long const length = std::distance(first, last);
    if (!length) {
        return init;
    }

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length+min_per_thread-1) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();

    unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads:2, max_threads);
    unsigned long const block_size = length/num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);

    Iterator block_start = first;
    for(unsigned long = 0; i < (num_threads-1); ++i){
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        thread[i] = std::thread(
                accumulate_block<Iterator, T>(),
                block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads-1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join()));
    return st::accumulate(results.begin(), results.end(), init);
}
