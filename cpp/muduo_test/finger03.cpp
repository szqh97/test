#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

using namespace muduo;
using namespace muduo::net;

void onConnection(const net::TcpConnectionPtr& conn)
{
    if (conn->connected())
    {
        conn->shutdown();
    }
}

int main ( int argc, char *argv[] )
{
    net::EventLoop loop;
    net::TcpServer server(&loop, net::InetAddress(1079), "Finger");
    server.start();
    loop.loop();
    return 0;
}			/* ----------  end of function main  ---------- */



