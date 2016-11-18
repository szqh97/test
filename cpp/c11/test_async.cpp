#include <iostream>
#include <thread>
#include <future>
#include <functional>

using namespace std;

void print_int(std::future<int>& fut)
{
    int x = fut.get();
    cout << "value: " << x << endl;
}

int main()
{
    std::future <int> f1 = std::async(std::launch::async, [](){return 9;});
    cout << f1.get() << endl;

    std::future<int> f2 = std::async(std::launch::async, [](){cout << "kk" << endl; return 9;});
    f2.wait();

    std::future<int> future = std::async(std::launch::async, [](){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return 10;
            });
    std::cout << "waiting ... \n";
    std::future_status status;
    do {
        status = future.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::deferred) {
            cout << "deferred" << endl;
        } else if (status == std::future_status::timeout) {
            cout << "timeout" << endl;
        } else if (status == std::future_status::ready) {
            cout << "ready!" << endl;
        } 
    } while (status != std::future_status::ready);
    cout << "result is " << future.get() << endl;


    std::promise<int> prom;
    prom.set_value(10);
    std::future<int> fut = prom.get_future();
    std::thread th1 (print_int, std::ref(fut));
    th1.join();

    std::promise<int> pr;
    std::thread t([](std::promise<int>& p) {p.set_value_at_thread_exit(999);}, std::ref(pr));
    //std::thread t([](std::promise<int>& p) {p.set_value(999);}, std::ref(pr));
    f1 = pr.get_future();
    auto r = f1.get();
    cout << "rrrr: " << r << endl;
    t.join();

    std::packaged_task<int()> task([](){std::this_thread::sleep_for(std::chrono::seconds(1));return -9;});
    f1 = task.get_future();
    std::thread t2(std::ref(task));
    t2.join();
    cout << "MMMMMM" << f1.get() << endl;



    return 0;
}
