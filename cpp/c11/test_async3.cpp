#include <iostream>
#include <future>
using namespace std;

int main()
{

     std::async(std::launch::async, [](){
            std::cout << "TESTSTSETEST" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(20));
            std::cout << "KKKKK" <<std::endl;
            });
    return 0;
}

