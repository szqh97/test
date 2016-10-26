#include <iostream>
#include <thread>
#include <vector>
#include <string.h>
void do_work(unsigned id){
    std::cout << std::this_thread::get_id() << std::ends << "---" << id << std::endl;
}

void f()
{
    std::vector<std::thread> threads;
    int i = 0;
    for (i = 0; i < 20; ++i) {
        threads.push_back(std::thread(do_work, i));
    }

    std::for_each(threads.begin(), threads.end(), 
            std::mem_fn(&std::thread::join));
}

int main()
{
    f();
    std::cout << std::thread::hardware_concurrency() << std::endl;
    return 0;
}

