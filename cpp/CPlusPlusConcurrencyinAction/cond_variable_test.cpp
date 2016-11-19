#include <mutex>
#include <iostream>
#include <condition_variable>
#include <queue>

typedef int data_chunk;
std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

void data_preparation_thread()
{
    while (true) {
        data_chunk const data = 1;
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }

}

void data_processing_thread()
{
    while(true) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [](){return !data_queue.empty();});
        data_chunk data = data_queue.front();
        data_queue.pop();
        lk.unlock();
        std::cout << "data: " << data << std::endl;
    }
}




int main()
{
    return 0;
}
