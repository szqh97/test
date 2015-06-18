#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

using namespace muduo;
using namespace muduo::net;


int main ( int argc, char *argv[] )
{
    net::EventLoop loop;
    net::TcpServer server(&loop, net::InetAddress(1079), "Finger");
    server.start();
    loop.loop();
    return 0;
}			/* ----------  end of function main  ---------- */


