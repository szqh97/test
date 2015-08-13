#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
class Printer
{
public:
    Printer(boost::asio::io_service &io ): timer_(io, boost::posix_time::seconds(1)), count(0)
    {
        timer_.async_wait(boost::bind(&Printer::print, this));
    }

    ~Printer()
    {
        std::cout << "Final count is: " << this->count << std::endl;
    }
    void print()
    {
        if (count < 5)
        {
            timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
            timer_.async_wait(boost::bind(&Printer::print, this));
            std::cout << "count: " << count << std::endl;
            ++count;

        }
    }


private:
    boost::asio::deadline_timer timer_;
    int count;
};

int main ( int argc, char *argv[] )
{

    boost::asio::io_service io;
    Printer p(io);
    io.run();

    return 0;
}			/* ----------  end of function main  ---------- */


