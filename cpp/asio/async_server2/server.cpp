#include "server.h"
#include <boost/lexical_cast.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>>
#include <algorithm>
#include <iterator>
using namespace std;


session::session(boost::asio::io_service& io_service) 
    : socket_(io_service){}

void session::start() {
    tcp::no_delay option(true);
    socket_.set_option(option);

    string client = boost::lexical_cast<string>(socket_.remote_endpoint());
    cout <<__FILE__<<":"<< __LINE__ << ": Client ["<< client <<"]("<< this <<")" << " connected..." << endl;
    boost::asio::async_read_until(socket_, sbuf_, "\n",
            boost::bind(&session::handle_read,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}


void session::handle_write(const boost::system::error_code& error, size_t bytes_transferred) {
    if (error) {
        string client = boost::lexical_cast<string>(this->socket_.remote_endpoint());
        std::cerr << __FILE__<< ":" <<__LINE__ << ": Client:[" << client << "](" << this << ") closed: " <<  boost::system::system_error(error).what() << endl;
        auto it = g_session_list.begin();
        while (it != g_session_list.end()) {
            if (it->get() == this) {
                it = g_session_list.erase(it);
            } else {
                ++it;
            }
        }
        return ;
    }

    boost::asio::async_read_until(socket_, sbuf_, "\n", 
            boost::bind(&session::handle_read, 
                shared_from_this(), 
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}


void session::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
    if (error) {
        string client = boost::lexical_cast<string>(this->socket_.remote_endpoint());
        std::cerr << __FILE__<< ":" <<__LINE__ << ": Client:[" << client << "](" << this << ") closed: " <<  boost::system::system_error(error).what() << endl;
        auto it = g_session_list.begin();

        while (it != g_session_list.end()) {
            if (it->get() == this) {
                it = g_session_list.erase(it);
            } else {
                ++it;
            }
        }
        return ;
    }

    boost::asio::async_write(socket_, sbuf_, 
            boost::bind(&session::handle_write,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

    
////////////////////
server::server(boost::asio::io_service& io_service, tcp::endpoint& endpoint) 
    : io_service_(io_service), acceptor_(io_service, endpoint), timer_(io_service, boost::posix_time::seconds(1)){
        session_ptr new_session (new session(io_service_));

#if 0
        acceptor_.async_accept(new_session->socket(),
            boost::bind(&server::handle_accept,
                    this, new_session, boost::asio::placeholders::error));
#endif

        acceptor_.async_accept(new_session->socket(),
                boost::bind(&server::handle_accept2,
                    this,new_session, boost::asio::placeholders::error));

}

#if 0
void server::run() {

    //timer_.async_wait(callback_);
    io_service_.run();
}
#endif

void server::handle_accept2(session_ptr new_session, const boost::system::error_code& error) {
if (error) {
        string client = boost::lexical_cast<string>(tcp::socket(this->io_service_).remote_endpoint());
        std::cerr << __FILE__<<":" <<  __LINE__ << ": Client: [" << client << "] closed: " << boost::system::system_error(error).what() << endl;
    }

//////FIXME add lock

    new_session->start();
    g_session_list.push_back(std::move(new_session));
    new_session.reset(new session(io_service_));
    cout << "g_session_list len is: " << g_session_list.size() << endl;


    acceptor_.async_accept(new_session->socket(), 
            boost::bind(&server::handle_accept2, this, new_session, boost::asio::placeholders::error));

}
void server::handle_accept(session_ptr new_session, const boost::system::error_code& error) {
    if (error) {
        string client = boost::lexical_cast<string>(tcp::socket(this->io_service_).remote_endpoint());
        std::cerr << __FILE__<<":" <<  __LINE__ << ": Client: [" << client << "] closed: " << boost::system::system_error(error).what() << endl;
    }

    new_session->start();
    new_session.reset(new session(io_service_));
    acceptor_.async_accept(new_session->socket(), 
            boost::bind(&server::handle_accept, this, new_session, boost::asio::placeholders::error));
}


