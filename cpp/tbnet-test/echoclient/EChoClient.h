#ifndef __CLIENTECHOPACKET_H_
#define _CLIENTECHOPACKET_H_ 1
#include <tbnet.h>
#define DATA_MAX_SIZE 4096
using namespace tbnet;
tbnet::Transport transport;
int gsendlen = 0;
class ClientEchoPacket : public Packet 
{
public:
    ClientEchoPacket();
    void setString(const std::string& str);
    virtual bool encode(DataBuffer *output);
    virtual bool decode(Databuffer *input, PacketHeader *header);
    std::string getString() const {return _str;}
    int getRecvLen() const { return _recvLen; }
    void free(){};
    int getIndex() const {return _index;}
    void setIndex(int i) {_index = i; };
private:
    std::string _str;
    int _recvLen;
    int _index;
    static int encode_count;
};

class ClientEchoPacketFactory: public IPacketFactory
{
public:
    Packet* createPacket(int pCode);
}

class ClientEchoPacketHandler : public IPacketHandler
{
public:
    ClientEchoPacketHandler();
    HPRetCode handlePacket(Packet *packet, void *args);
private:
    atomic_t _count;
    int64_t _recvlen; 
    int _timeoutCount;
    static int send_count;
};


class EchoClient
{
public:
    EchoClient(char *spec);
    ~EchoClient();
    void start(int c);
private:
    char *_spec;
};
#endif /* ifndef _CLIENTECHOPACKET_H_ 1
#include <tbnet.h> */
