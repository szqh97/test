#include <iostream>
#include <boost/asio.hpp>
#include <string.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using std::cin;
using std::cout;
using std::endl;
using boost::asio::ip::tcp;
using boost::asio::ip::address;

class session : public boost::enable_shared_from_this<session> {
public:
    session(boost::asio::io_service &io_service): socket_(io_service) {}
    void start() {
        //static tcp::no_delay option(true);
        tcp::no_delay option(true);
        socket_.set_option(option);

        boost::asio::async_read_until(
                socket_, 
                sbuf_, 
                "\n",
                boost::bind(&session::handle_read,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                )
                );
    }

    tcp::socket &socket() { return socket_; }

private:
    void handle_write(const boost::system::error_code&  error, size_t bytes_transferred) {
        if (error) {
            std::cout << error << "----" << std::endl;
            delete this;
            return;
        }
        if (socket_.is_open() ) {
            boost::asio::async_read_until(socket_,
                    sbuf_,
                    "\n",
                    boost::bind(&session::handle_read,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred
                        ));
            std::cout << "in handle write" << std::endl;

        }
    }

    void handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
        if (error) {
            cout << boost::system::system_error(error).what() << endl;
            return;
        }
#if 0
        std::cout << error.message() << std::endl;
        if (error.value() == boost::asio::error::eof) {
            return;
        }
#endif
        boost::asio::async_write(socket_,
                sbuf_,
                boost::bind(&session::handle_write,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }


private:
    tcp::socket socket_;
    boost::asio::streambuf sbuf_;
};

typedef boost::shared_ptr<session> session_ptr;

class server {
public:
    server(boost::asio::io_service& io_service, tcp::endpoint &endpoint)
        : io_service_(io_service), acceptor_(io_service, endpoint){
            session_ptr new_session(new session(io_service_));
            acceptor_.async_accept(new_session->socket(),
                    boost::bind(&server::handle_accept,
                        this, 
                        new_session,
                        boost::asio::placeholders::error));

        }
    void handle_accept(session_ptr new_session, const boost::system::error_code& error) {
        if (error) {
            return;
        }
        new_session->start();
        new_session.reset(new session(io_service_));
        acceptor_.async_accept(new_session->socket(), 
                boost::bind(&server::handle_accept, this, new_session, boost::asio::placeholders::error));
    }

    void run() {
        io_service_.run();
    }

private:
    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
};


int main(int argc, char *argv[])
{
    boost::asio::io_service io_service;
    tcp::endpoint endpoint(tcp::v4(), 9999);

    server s(io_service, endpoint);
    s.run();
    return 0;


    return 0;
}
