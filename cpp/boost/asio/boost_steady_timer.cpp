#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
using namespace boost::asio;
int main()
{
    boost::asio::io_service ioservice;
    boost::asio::steady_timer timer {ioservice, boost::chrono::seconds{3}};
    timer.async_wait([](const boost::system::error_code &ec)
    { std::cout << "3 sec\n"; })
    ioservice.run();
    return 0;
}
