#include <muduo/net/TcpServer.h>
#include <boost/bind.hpp>
#include <iostream>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <algorithm>
#include <boost/implicit_cast.hpp>
#include "sudoku.h"

using namespace muduo;
//#define LOG_INFO std::cout

class SudoKuServer
{
    public:
        SudoKuServer(muduo::net::EventLoop* loop, 
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


SudoKuServer::SudoKuServer(muduo::net::EventLoop* loop, 
        const muduo::net::InetAddress& listenAddr)
    :loop_(loop), server_(loop, listenAddr, "SudoKuServer")
{
    server_.setConnectionCallback(boost::bind(&SudoKuServer::onConnection, this, _1));
    server_.setMessageCallback(boost::bind(&SudoKuServer::onMessage, this, _1, _2, _3));
}

void SudoKuServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
    LOG_INFO<< "SudoKuServer - " << conn->peerAddress().toIpPort() << " -> " 
            << conn->localAddress().toIpPort() << " is " 
            << (conn->connected() ? "UP" : "DOWN");
}

const int kCell = 81;
void SudoKuServer::onMessage(const muduo::net::TcpConnectionPtr& conn, 
        muduo::net::Buffer* buf, muduo::Timestamp time)
{
    LOG_DEBUG << conn->name();
    size_t len = buf->readableBytes();
    while (len >= kCell + 2)
    {
        const char* crlf = buf->findCRLF();
        if(crlf)
        {
            string request(buf->peek(), crlf);
            string id;
            buf->retrieveUntil(crlf + 2);
            string::iterator colon = find(request.begin(), request.end(), ':');
            if (colon != request.end())
            {
                id.assign(request.begin(), colon);
                request.erase(request.begin(), colon + 1);
            }
            if (request.size() == boost::implicit_cast<size_t>(kCell))
            {
                string result = solveSudoku(request);
                if (id.empty())
                {
                    conn->send(result + "\r\n");
                }
                else
                {
                    conn->send(id + ":" + result + "\r\n");
                }
            }
            else
            {
                conn->send("Bad Request!\r\n");
            }
        }
        else
        {
            break;
        }

    }
}

void SudoKuServer::start()
{
    server_.start();
}

int main ( int argc, char *argv[] )
{
    LOG_INFO << "pid= " << getpid() ;
    muduo::net::EventLoop loop;
    muduo::net::InetAddress listenAddr(9981);
    SudoKuServer server(&loop, listenAddr);
    server.start();
    loop.loop();
    return 0;
}	
