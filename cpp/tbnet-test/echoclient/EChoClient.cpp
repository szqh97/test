#include "EChoClient.h"
#include <ipackethandler.h>
int ClientEchoPacket::encode_count = 0;
ClientEchoPacket::ClientEchoPacket()
{
    _recvLen = 0;
    _index = 0;
}

void ClientEchoPacket::setString(char* str)
{
    strncpy(_str, str, DATA_MAX_SIZE);
    _str[DATA_MAX_SIZE] = '\0';
}

bool ClientEchoPacket::encode(DataBuffer *output)
{
    output->writeBytes(_str, strlen(_str));
    encode_count++;
    return true;
}

bool ClientEchoPacket::decode(DataBuffer *input, PacketHeader *header)
{
    _recvLen = header->_dataLen;
    int len = header->_dataLen;
    if (len >= DATA_MAX_SIZE) {
        len = DATA_MAX_SIZE - 1;
    }
    input->readBytes(_str, len);
    _str[len] = '\0';
    if (header->_dataLen > len) {
        input->drainData(header->_dataLen - len);
    }

    return true;
}

Packet* ClientEchoPacketFactory::createPacket(int pcode)
{
    return new ClientEchoPacket();
}

///////////
int ClientEchoPacketHandler::send_count = 0;
ClientEchoPacketHandler::ClientEchoPacketHandler()
{
    _recvlen = 0;
    _timeoutCount = 0;
    atomic_set(&_count, 0);
}

IPacketHandler::HPRetCode ClientEchoPacketHandler::handlePacket(Packet *packet, void *args)
{
    ClientEchoPacket *echopacket = (ClientEchoPacket*) args;
    atomic_inc(&_count);
    if (!packet->isRegularPacket())
    {
        TBSYS_LOG(ERROR, "INDEX %d => Contropacket: %d", echopacket->getIndex(), ((ControlPacket*)packet)->getCommand());
        _timeoutCount++;
        if (_count.counter == send_count) {
            transport.stop();
        }
        delete echopacket;
        return IPacketHandler::FREE_CHANNEL;
    }
    _recvlen += ((ClientEchoPacket*)packet)->getRecvLen();
    if (_count.counter == send_count) {
        TBSYS_LOG(INFO, "INDEX: %d OK => _count: %d gsendlen: %lld == %lld, _timeoutCount: %d", echopacket->getIndex(), _count.counter, gsendlen, _recvlen, _timeoutCount);
        transport.stop();
    } else {
        TBSYS_LOG(INFO, "INDEX: %d _count: %s gsendlen: %lld == %lld, _timeoutCount: %d", echopacket->getIndex(), _count.counter, gsendlen, _recvlen, _timeoutCount);
    }

    delete echopacket;
    delete packet;
    return IPacketHandler::FREE_CHANNEL;
}

///////////
EchoClient::EchoClient(char *spec)
{
    _spec = strdup(spec);
}

EchoClient::~EchoClient()
{
    if(_spec){
        delete _spec;
        _spec = NULL;
    }
}

void EchoClient::start(int c)
{
    ClientEchoPacketFactory factory;
    tbnet::DefaultPacketStreamer streamer(&factory);
    ClientEchoPacketHandler handler;
    Connection **cons = (Connection**) malloc(c*sizeof(Connection*));

    for (int i = 0; i < c ; ++c) {
        cons[i] = transport.connect(_spec, &streamer, true);
        if (cons[i] == NULL) {
            TBSYS_LOG(ERROR, "connection error..");
            return;
        }
        cons[i]->setDefaultPacketHandler(&handler);
        cons[i]->setQueueLimit(500);
    }
    transport.start();
    char buffer[DATA_MAX_SIZE + 1];
    int sendcount = 0;
    int pid = getpid();
    TBSYS_LOG(INFO, "PID: %d", pid);

    for (int i = 0; i < gsendcount; ++i) {
        int len = 1988;
        sprintf(buffer, "%010d_%010d", pid, i);
        memset(buffer+21, 'a', len-21);
        buffer[len] = '\0';
        ClientEchoPacket *packet = new ClientEchoPacket();
        packet->setIndex(i);
        packet->setString(buffer);
        if (!cons[i%c]->postPacket(packet, NULL, packet)) {
            break;
        }
        gsendlen += len;
        sendcount ++;
    }
    gsendcount = sendcount;
    TBSYS_LOG(ERROR, "send finish.");
    transport.wait();
    free(cons);
}


void singalHander(int sig)
{
    transport.stop();
}
