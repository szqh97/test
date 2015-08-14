#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio.hpp>

class Printer
{
public:
    Printer(boost::asio::io_service &io):
        strand_(io),
        timer1_(io, boost::posix_time::seconds(1)),
        timer2_(io, boost::posix_time::seconds(1)),
        count_(0)
    {
        timer1_.async_wait(strand_.wrap(boost::bind(&Printer::print1, this)));
        timer2_.async_wait(strand_.wrap(boost::bind(&Printer::print2, this)));
    }
    
    ~Printer()
    {
        std::cout<< "Final count is: " << count_ << std::endl;
    }

    void print1();
    void print2();
#if 0
    void print1()
    {
        if (count_ < 10)
        {
            timer2_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
            timer2_.async_wait(strand_.wrap(boost::bind(&Printer::print2, this)));

            std::cout << "Printer::print2 count: " << count_ << std::endl;
            ++count_;
        }
    }

    void print2()
    {
        if (count_ < 10)
        {
            timer2_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
            timer2_.async_wait(strand_.wrap(boost::bind(&Printer::print2, this)));

            std::cout << "Printer::print2 count: " << count_ << std::endl;
            ++count_;
        }

    }
#endif 
private:
    boost::asio::io_service::strand strand_;
    boost::asio::deadline_timer timer1_;
    boost::asio::deadline_timer timer2_;
    int count_;

};

#if 1

void Printer::print1()
{
    if (count_ < 10)
    {
        timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
        timer1_.async_wait(strand_.wrap(boost::bind(&Printer::print1, this)));

        std::cout << "Printer::print1 count: " << count_ << std::endl;
        ++count_;
    }
}

void Printer::print2()
{
    if (count_ < 10)
    {
        timer2_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
        timer2_.async_wait(strand_.wrap(boost::bind(&Printer::print2, this)));

        std::cout << "Printer::print2 count: " << count_ << std::endl;
        ++count_;
    }
}
#endif

int main ( int argc, char *argv[] )
{

    boost::asio::io_service io;
    Printer p(io);
    boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
    io.run();
    t.join();
    return 0;
}			/* ----------  end of function main  ---------- */

