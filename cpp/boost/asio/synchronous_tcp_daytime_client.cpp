#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main ( int argc, char *argv[] )
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage ./a.out <host>" << std::endl;
            return 1;
        }
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], "daytime");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        for(;;)
        {
            boost::array<char, 128> buff;
            boost::system::error_code error;
            
            size_t len = socket.read_some(boost::asio::buffer(buff), error);
            
            if (error == boost::asio::error::eof)
            {
                break;
            }
            else if (error)
            {
                throw boost::system::system_error(error);
            }
            std::cout.write(buff.data(), len);
        }

    }
    catch (std::exception &err)
    {
        std::cerr << err.what() << std::endl;
    }
    return 0;
}			/* ----------  end of function main  ---------- */

