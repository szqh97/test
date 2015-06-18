#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <muduo/base/Logging.h>

using namespace muduo;
using namespace muduo::net;

void onMessage(const TcpConnectionPtr& conn, 
        net::Buffer* buf, Timestamp time)
{
    if(buf->findCRLF())
    {
        conn->send("No such User\n\r");
        LOG_INFO << "before shutdown " ;
        conn->shutdown();
    }
}

int main ( int argc, char *argv[] )
{
    net::EventLoop loop;
    net::TcpServer server(&loop, net::InetAddress(1079), "Finger");
    server.setMessageCallback(onMessage);
    server.start();
    loop.loop();
    return 0;
}			/* ----------  end of function main  ---------- */



