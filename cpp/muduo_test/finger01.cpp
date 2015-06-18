#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;


int main ( int argc, char *argv[] )
{
    net::EventLoop loop;
    loop.loop();
    return 0;
}			/* ----------  end of function main  ---------- */

