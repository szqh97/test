#include <iostream>
#include <ctime>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::udp;

std::string make_daytime_string()
{
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

int main()
{
    try
    {
        boost::asio::io_service io;
        udp::socket socket(io, udp::endpoint(udp::v4(), 13));
        for (;;)
        {
            boost::array<char, 1> recv_buf;
            udp::endpoint remote_endpoint;
            boost::system::error_code error;
            socket.receive_from(boost::asio::buffer(recv_buf),
                    remote_endpoint, 0, error);
            if (error && error != boost::asio::error::message_size)
                throw boost::system::system_error(error);
            std::string message = make_daytime_string();
            boost::system::error_code ignore_error;
            socket.send_to(boost::asio::buffer(message), 
                    remote_endpoint, 0, ignore_error);

        }
    }
    catch (std::exception& err)
    {
        std::cerr<< err.what() << std::endl;
        
    }
    
    return 0;
}
