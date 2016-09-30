#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <unistd.h>
using namespace boost::asio;
using namespace std;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
void client_session(socket_ptr sock)
{
    while(true) 
    {
        char data[512];
        size_t len = sock->read_some(buffer(data));
        if (len > 0)
        {
            sock->write_some(buffer("ok", 2));
        }
    }
}
int main()
{
    io_service ioservice;
    ip::tcp::endpoint ep (ip::tcp::v4(), 2001);
    ip::tcp::acceptor acc(ioservice, ep);
    while (true) {
        socket_ptr sock(new ip::tcp::socket(ioservice));
        acc.accept(*sock);
        thread(boost::bind(client_session, sock));
    }

    return 0;
}
