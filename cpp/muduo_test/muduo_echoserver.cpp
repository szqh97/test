#include <muduo/net/TcpServer.h>
#include <boost/bind.hpp>
#include <iostream>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

//#define LOG_INFO std::cout

class EchoServer
{
    public:
        EchoServer(muduo::net::EventLoop* loop, 
                const muduo::net::InetAddress& listenAddr);

        void start();
    private:
        void onConnection(const muduo::net::TcpConnectionPtr& conn);

        void onMessage(const muduo::net::TcpConnectionPtr& conn,
                muduo::net::Buffer* buf,
                muduo::Timestamp time);
    private:
        muduo::net::EventLoop* loop_;
        muduo::net::TcpServer server_;
};


EchoServer::EchoServer(muduo::net::EventLoop* loop, 
        const muduo::net::InetAddress& listenAddr)
    :loop_(loop), server_(loop, listenAddr, "EchoServer")
{
    server_.setConnectionCallback(boost::bind(&EchoServer::onConnection, this, _1));
    server_.setMessageCallback(boost::bind(&EchoServer::onMessage, this, _1, _2, _3));
}

void EchoServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
    LOG_INFO<< "EchoServer - " << conn->peerAddress().toIpPort() << " -> " 
            << conn->localAddress().toIpPort() << " is " 
            << (conn->connected() ? "UP" : "DOWN");
}

void EchoServer::onMessage(const muduo::net::TcpConnectionPtr& conn, 
        muduo::net::Buffer* buf, muduo::Timestamp time)
{
    muduo::string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, " 
             << "data received at " << time.toString();
    conn->send(msg);
}

void EchoServer::start()
{
    server_.start();
}

int main ( int argc, char *argv[] )
{
    LOG_INFO << "pid= " << getpid() ;
    muduo::net::EventLoop loop;
    muduo::net::InetAddress listenAddr(2007);
    EchoServer server(&loop, listenAddr);
    server.start();
    loop.loop();
    return 0;
}	
