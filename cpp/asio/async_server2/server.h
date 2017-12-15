#ifndef SERVER_H_
#define SERVER_H_ 

#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::address;

class session : public boost::enable_shared_from_this<session> {
public:
    session(boost::asio::io_service& io_service);
    void start();
    tcp::socket& socket() {return socket_;}
private:
    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    
private:
    tcp::socket socket_;
    boost::asio::streambuf sbuf_;
};

typedef boost::shared_ptr<session> session_ptr;

class server {
public:
    server(boost::asio::io_service& io_service, tcp::endpoint& endpoint);
    void handle_accept(session_ptr new_session, const boost::system::error_code& error);
    void run() {io_service_.run();}
private:

    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
};

#endif /* ifndef SERVER_H_ */
