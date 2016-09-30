#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <thread>
#include <iostream>
using namespace boost::asio;
int main()
{
    io_service ioservice1;
    io_service ioservice2;
    steady_timer timer1{ioservice1, std::chrono::seconds{3}};
    timer1.async_wait([](const boost::system::error_code &ec){
            std::cout << "3 sec" << std::endl;
            });
    steady_timer timer2{ioservice2, std::chrono::seconds{3}};
    timer2.async_wait([](const boost::system::error_code &ec){
            std::cout << "3 sec" << std::endl;
            });
    std::thread t1{[&ioservice1]{ioservice1.run();}};
    std::thread t2{[&ioservice2]{ioservice2.run();}};
    t1.join();
    t2.join();
    return 0;
}
