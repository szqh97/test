#include <ctime>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

class tcp_connection:
    public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;
    static pointer create(boost::asio::io_service& io)
    {
        return pointer(new tcp_connection(io));
    }
    
    tcp::socket& get_socket()
    {
        return socket_;
    }

    void start()
    {
        message_ = make_daytime_string();
        boost::asio::async_write(socket_, boost::asio::buffer(message_), 
                boost::bind(&tcp_connection::hander_writte, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }

private:
    tcp_connection(boost::asio::io_service& io_service):
        socket_(io_service)
    {
    }
    void hander_writte(const boost::system::error_code&,size_t)
    {
    }
    

    tcp::socket socket_;
    std::string message_;
};

class tcp_server
{
public:
   tcp_server(boost::asio::io_service& io ) :
       acceptor_(io, tcp::endpoint(tcp::v4(), 13))
    {
        start_accept();
    }

private:
   void start_accept()
   {
       tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_io_service());

       acceptor_.async_accept(new_connection->get_socket(), 
               boost::bind(&tcp_server::handler_accept, this, new_connection,
                   boost::asio::placeholders::error));
#if 0
       acceptor_.async_accept(new_connection->get_socket(), 
               boost::bind(&tcp_server::handler_accept, this, new_connection,
                   boost::asio::placeholders::error));
#endif
   }

   void handler_accept(tcp_connection::pointer connection, boost::system::error_code& err)
   {
       if (!err)
       {
           connection->start();
       }
       start_accept();
   }
    tcp::acceptor acceptor_;
};
int main ()
{
    try
    {
        boost::asio::io_service io;
        tcp_server server(io);
        io.run();

    }
    catch (std::exception& err)
    {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}			/* ----------  end of function main  ---------- */
