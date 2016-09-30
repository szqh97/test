#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

int main()
{
    using namespace boost::asio;
    io_service ioservice;
    ip::tcp::endpoint ep (ip::address::from_string("127.0.0.1"), 2001);
    ip::tcp::socket sock(ioservice);
    sock.connect(ep);
    return 0;
}
