#include <iostream>
#include <thread>
#include <future>
using namespace std;

int task(int x)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return x;
}
int main()
{
    std::future<int> f1 = std::async(std::launch::async, [](){return 9;});
    std::future<void> f2 = std::async(std::launch::async, [](){cout << 8 << endl;});
    cout << f1.get() << endl;
    f2.wait();

    std::future<int> f3 = std::async(std::launch::async, [](){
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return 10;
            });

    std::future_status status;
    do {
        status = f3.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::deferred){
            cout << "deferred\n" << endl;
        } else if (status == std::future_status::timeout) {
        } else if (status == std::future_status::ready) {
            cout << "ready" << endl;
        } 
    }while (status  != std::future_status::ready);
    cout << f3.get() << endl;

    std::future<int> myf = std::async(task , 11);
    std::future<int> myf2 = std::async(std::launch::async, task, 11);
    cout << "kkkk" << myf.get() << endl;
    cout << "kkkk" << myf2.get() << endl;

    return 0;

}
