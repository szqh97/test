#include "server.h"
int main()
{
    boost::asio::io_service io_service;
    tcp::endpoint endpoint(tcp::v4(), 9999);

    server s(io_service, endpoint);
    s.run();
    return 0;
}
