#include <iostream>
#include <boost/asio.hpp>
#include <ctime>
#include <string>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

int main ( int argc, char *argv[] )
{
    try
    {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
        for (;;)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::string message = make_daytime_string();
            boost::system::error_code ignore_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignore_error);
        }

    }
    catch (std::exception &err)
    {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}			/* ----------  end of function main  ---------- */



