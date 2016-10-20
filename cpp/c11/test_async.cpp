#include <iostream>
#include <thread>
#include <future>
using namespace std;
int main()
{
    std::future <int> f1 = std::async(std::launch::async, [](){return 9;});
    cout << f1.get() << endl;

    std::future<int> f2 = std::async(std::launch::async, [](){cout << "kk" << endl; return 9;});
    f2.wait();

    std::future<int> future = std::async(std::launch::async, [](){
            std::this_thread::sleep_for(std::chrono::seconds(4));
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
    return 0;
}
