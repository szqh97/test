#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/local_time/local_time.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::address;

class client : public boost::enable_shared_from_this<client> {
public:
    client(boost::asio::io_service& io_service, tcp::endpoint &endpoint) 
        : io_service_(io_service), socket_(io_service), endpoint_(endpoint) {}

    void start() {
        socket_.async_connect(endpoint_, 
                boost::bind(&client::handle_connect, 
                    shared_from_this(),
                    boost::asio::placeholders::error)
                );
        
    }
private:
    void handle_connect(const boost::system::error_code& error) {
        if (error) {
            if (error.value() != boost::system::errc::operation_canceled) {
                std::cerr << boost::system::system_error(error).what() << std::endl;
            }
            socket_.close();
            return;
        }
        tcp::no_delay option(true);
        socket_.set_option(option);

        strcpy(buf, "hello world\n");
        boost::asio::async_write(socket_,
                boost::asio::buffer(buf, strlen(buf)),
                boost::bind(&client::handle_write, 
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred)
                );
    }

    void handle_write(const boost::system::error_code& error, size_t bytes_transferred) {
        memset(buf, sizeof(buf),0);
        boost::asio::async_read_until(socket_, sbuf, "\n",
                boost::bind(&client::handle_read,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred)
                );
    }

    void handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
        std::cout << buf << std::endl;
        strcpy(buf, "hello world\n");
        boost::asio::async_write(socket_,
                boost::asio::buffer(buf, strlen(buf)),
                boost::bind(&client::handle_write,
                    shared_from_this(), 
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred)
                );
    }

private:
    boost::asio::io_service& io_service_;
    tcp::socket socket_;
    tcp::endpoint &endpoint_;
    char buf[1024];
    boost::asio::streambuf sbuf;
};

typedef boost::shared_ptr<client> client_ptr;
int main(int argc, char *argv[])
{
    boost::asio::io_service io_service;
        
    tcp::endpoint endpoint(address::from_string("127.0.0.1"), 9999);
    client_ptr new_client(new client(io_service, endpoint));
    new_client->start();
    io_service.run();

    return 0;
}

