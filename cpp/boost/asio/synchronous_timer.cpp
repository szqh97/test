/*
 * g++ -g --std=c++11 synchronous_timer.cpp -lboost_system
 */
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define V3 1
void print_inf(const boost::system::error_code& /* e */)
{
    std::cout << "Hello xxxx" << std::endl;
}

void print_inf2(const boost::system::error_code & /* e */,
        boost::asio::deadline_timer* t, int* count)
{
    if (*count < 5)
    {
        std::cout << "count: " << *count << std::endl;
        ++(*count);
        
        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        t->async_wait(boost::bind(print_inf2, boost::asio::placeholders::error, t, count));
    }
    
}

int main ( int argc, char *argv[] )
{
    int count = 0;
    boost::asio::io_service io;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
    // v1 timer asio
#if V1
    t.wait();
    std::cout << "hello world" << std::endl;
#endif

#if V2
    t.async_wait(&print_inf);
    io.run();
#endif

#if V3
    t.async_wait(boost::bind(print_inf2, boost::asio::placeholders::error, &t, &count));
    io.run();

    std::cout << "Final count is: " << count << std::endl;
#endif

    return 0;
}			/* ----------  end of function main  ---------- */

