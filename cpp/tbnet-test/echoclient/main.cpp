#include  "EChoClient.h"
#include <iostream>
#include <signal.h>
using namespace std;
int main(int argc, char *argv[])
{
    if (argc != 4) {
        cout << argv[0] << "[tcp|udp]:ip:port count conn" << endl;
        return 0;
    }

    int sendcount = atoi(argv[2]);
    if (sendcount > 0) {
        gsendcount = sendcount;
    }
    int conncount = atoi(argv[3]);
    if (conncount < 1) {
        conncount = 1;
    }

    signal(SIGINT, singalHander);
    signal(SIGTERM, singalHander);

    EchoClient client(argv[1]);
    client.start(conncount);


    return 0;
}
