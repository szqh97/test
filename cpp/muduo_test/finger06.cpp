#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <muduo/base/Logging.h>
#include <string>
#include <map>

using namespace muduo;
using namespace muduo::net;

typedef std::map<std::string, std::string> UserMap;
UserMap users;

std::string getUser(const std::string& user)
{
    std::string result = "No Such user";
    UserMap::iterator it = users.find(user);
    if (it != users.end())
    {
        result = it->second;
    }
    return result;
}

void onMessage(const TcpConnectionPtr& conn, 
        net::Buffer* buf, Timestamp time)
{
    const char* crlf = buf->findCRLF();
    if(crlf)
    {
        std::string user(buf->peek(), crlf);
        conn->send(getUser(user) + "\r\n");
        buf->retrieveUntil(crlf + 2);
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




