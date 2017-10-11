#include "tcpsocket.h"

#define log cout<<"["<<__FILE__<<"("<<__LINE__<<")]<"<<__FUNCTION__<< "> "

#define CHECK_IRET(iret) { \
    if (iret) { \
        errmsg_ = getUVError(iret); \
        cerr << __LINE__ << errmsg_ << endl; \
        return false; \
    } \
}

using namespace std;

std::string getUVError(int retcode){
    std::string err;
    err = uv_err_name(retcode);
    err += ":";
    err += uv_strerror(retcode);
    return std::move(err);
}



UV_NAMESPACE_BEGIN

/****************** TCPServer ****************/


TCPServer::TCPServer(uv_loop_t* loop):newconnectcb_(nullptr), isinit_(false), loop_(loop){}

TCPServer::~TCPServer(){
    close();
    std::cout << "tcp server exit" << std::endl;
}

bool TCPServer::init() {
    if (isinit_) {
        return true;
    }
    if (!loop_) {
        errmsg_ = "loop is null on tcp init.";
        cerr << __LINE__ <<errmsg_ << endl;
        return false;
    }

    int iret = uv_mutex_init(&mutex_handle_);
    if (iret) {
        errmsg_ = getUVError(iret);
        cerr << __LINE__ << errmsg_ << endl;
        return false;
    }

    iret = uv_tcp_init(loop_, &server_);
    CHECK_IRET(iret);

    isinit_ = true;
    server_.data = this;

    return true;
}


void TCPServer::close() {
    for (auto it = clients_list_.begin(); it != clients_list_.end(); ++it) {
        auto data = it->second;
        uv_close((uv_handle_t*)data->client_handle, afterClientClosed);
    }
    clients_list_.clear();

    log << "close server" << endl;
    if (isinit_) {
        uv_close((uv_handle_t*) &server_, afterServerClosed);
        log << "close server " << endl;
    }

    isinit_ = false;
    uv_mutex_destroy(&mutex_handle_);
}

bool TCPServer::run(int status) {
    log << "server running" << endl;
    int iret = uv_run(loop_, (uv_run_mode)status);
    CHECK_IRET(iret);
    return true;
}

bool TCPServer::setKeepAlive(int enable, unsigned int delay) {
    int iret = uv_tcp_keepalive(&server_, enable, delay);
    CHECK_IRET(iret);
    return true;
}

bool TCPServer::bind(const char* ip, int port) {
    struct sockaddr_in bind_addr;
    int iret = uv_ip4_addr(ip, port, &bind_addr);
    CHECK_IRET(iret);
    iret = uv_tcp_bind(&server_, (const struct sockaddr*)&bind_addr, 0);
    CHECK_IRET(iret);
    log << "server bind ip=" << ip << ", port="<< port <<endl;
    return true;
}

bool TCPServer::bind6(const char* ip, int port) {
    struct sockaddr_in6 bind_addr;
    int iret = uv_ip6_addr(ip , port, &bind_addr);
    CHECK_IRET(iret);
    iret = uv_tcp_bind(&server_, (const struct sockaddr*)&bind_addr, 0);
    CHECK_IRET(iret);
    log << "server bind ip=" << ip << ", port="<< port <<endl;
    return true;
}

bool TCPServer::listen(int backlog) {
    int iret = uv_listen((uv_stream_t*)&server_, backlog, acceptConnection);
    CHECK_IRET(iret);
    log << "server listening ..." << endl;
    return true;
}

bool TCPServer::start(const char *ip, int port) {
    close();
    if (!init()) return false;
    if (!bind(ip, port)) return false;
    if (!listen(SOMAXCONN)) return false;
    if (!run()) return false;
    log << "start listen" << ip << ":" << port << endl;
    return true;
}

bool TCPServer::start6(const char *ip, int port) {
    close();
    if (!init()) return false;
    if (!bind6(ip, port)) return false;
    if (!listen(SOMAXCONN)) return false;
    if (!run()) return false;
    log << "start listen" << ip << ":" << port << endl;
    return true;
}

int TCPServer::send(int clientid, const char* data, std::size_t len) {
    auto itfind = clients_list_.find(clientid);
    if (itfind == clients_list_.end()) {
        errmsg_ = "can't find clientid: " + std::to_string(clientid);
        cerr << __LINE__ << errmsg_ << endl;
        return -1;
    }

    //自己控制data的生命周期直到write结束
    auto itbuffer = itfind->second->writebuffer;
    if (itbuffer.len < len) {
        itbuffer.len = len;
        itbuffer.base = (char*) realloc(itbuffer.base, len);
    }
    memcpy(itbuffer.base, data, len);
    uv_buf_t buf = uv_buf_init((char*)itbuffer.base, len);
    int iret = uv_write(&itfind->second->write_req, 
            (uv_stream_t*)itfind->second->client_handle, &buf, 1, afterSend);
    CHECK_IRET(iret);
    return true;
}

void TCPServer::acceptConnection(uv_stream_t* server,  int status) {
    if (!server->data) return ;

    TCPServer *tcpsock = (TCPServer*)server->data;
    int clientId = tcpsock->getAvailableClientId();
    ClientData* cdata = new ClientData(clientId);
    cdata->tcp_server = tcpsock;
    int iret = uv_tcp_init(tcpsock->loop_, cdata->client_handle);
    if (iret) {
        delete cdata;
        tcpsock->errmsg_ = getUVError(iret);
        cerr << __LINE__ << tcpsock->errmsg_ << endl;
        return;
    }
    iret = uv_accept((uv_stream_t*)&tcpsock->server_, (uv_stream_t*)cdata->client_handle);
    if (iret) {
        tcpsock->errmsg_ = getUVError(iret);
        uv_close((uv_handle_t*)cdata->client_handle, NULL);
        delete cdata;
        cerr << __LINE__ << tcpsock->errmsg_ << endl;
        return;
    }

    tcpsock->clients_list_.insert(std::make_pair(clientId, cdata));
    if(tcpsock->newconnectcb_) {
        tcpsock->newconnectcb_(clientId);
    }
    log << "new client (" << cdata->client_handle << ") id = " << clientId << endl;
    iret = uv_read_start((uv_stream_t*)cdata->client_handle, onAllocBuffer, afterServerRecv);
    return;
}

void TCPServer::setRecvCB(int clientId, server_recvcb cb){
    auto itfind = clients_list_.find(clientId);
    if (itfind != clients_list_.end()) {
        itfind->second->recvcb_ = cb;
    }
}

void TCPServer::setNewConnectCB(newconnect cb) {
    newconnectcb_ = cb;
}

void TCPServer::onAllocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    if (!handle->data) return;
    ClientData *client = (ClientData*) handle->data;
    *buf = client->readbuffer;
}

void TCPServer::afterServerRecv(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf){
    if (!handle->data) return;
    ClientData *client = (ClientData*)handle->data;
    if (nread < 0) {
        TCPServer *server = (TCPServer*)client->tcp_server;
        if (nread == UV_EOF) {
            fprintf(stdout, "client (%d) disconnected, close it\n", client->client_id);
        } else if (nread == UV_ECONNRESET) {
            fprintf(stdout, "client (%d) disconnect abnormal\n", client->client_id);
        } else {
            log << getUVError(nread) << endl;
        }
        server->deleteClient(client->client_id);
        return;
    } else if (0 == nread) {

    } else if (client->recvcb_) {
        client->recvcb_(client->client_id, buf->base, nread);
    }
}

void TCPServer::afterSend(uv_write_t *req, int status) {
    if (status < 0) {
        cerr << __LINE__ << "send data error" << getUVError(status) << endl;
    }
}

void TCPServer::afterServerClosed(uv_handle_t *handle) {}

void TCPServer::afterClientClosed(uv_handle_t *handle) {
    ClientData *cdata = (ClientData*)handle->data;
    log << "client " << cdata->client_id << " had closed." <<endl;
    delete cdata;
}

int TCPServer::getAvailableClientId() const {
    static int s_id = 0;
    return ++s_id;
}

bool TCPServer::deleteClient(int clientId) {
    uv_mutex_lock(&mutex_handle_);
    auto itfind = clients_list_.find(clientId);
    if (itfind == clients_list_.end()) {
        errmsg_ = "can't find client ";
        errmsg_ += std::to_string(clientId);
        log << errmsg_  << endl;
        uv_mutex_unlock(&mutex_handle_);
        return false;
    }
    if (uv_is_active((uv_handle_t*)itfind->second->client_handle)) {
        uv_read_stop((uv_stream_t*)itfind->second->client_handle);
    }
    uv_close((uv_handle_t*)itfind->second->client_handle, afterClientClosed);

    clients_list_.erase(itfind);
    log << "delete client " << clientId << endl;
    uv_mutex_unlock(&mutex_handle_);
    return true;
}
void TCPServer::startLog(const char* logpath ) {}


/****************** TCPClient **********************/
TCPClient::TCPClient(uv_loop_t* loop)
     : recvcb_(nullptr), userdata_(nullptr)
     , connectionstatus_(CONNECT_DIS), isinit_(false)  {
         loop_ = loop;
         readbuffer_ = uv_buf_init((char*) malloc(BUFFERSIZE), BUFFERSIZE);
         writebuffer_ = uv_buf_init((char*) malloc(BUFFERSIZE), BUFFERSIZE);
         connect_req_.data = this;
         write_req_.data = this;
  }

TCPClient::~TCPClient() {
    free(readbuffer_.base);
    readbuffer_.base = nullptr;
    readbuffer_.len = 0;

    free (writebuffer_.base);
    writebuffer_.base = nullptr;
    writebuffer_.len = 0;

    close();
    log << "client (" << this << ") exit." << endl;
}


bool TCPClient::init() {
    if (isinit_) {
        return true;
    }

    if (!loop_) {
        errmsg_ = "loop is null on tcp init.";
        log << errmsg_ << endl;
        return false;
    }

    int iret = uv_tcp_init(loop_, &client_);
    CHECK_IRET(iret);
    iret = uv_mutex_init(&write_mutex_handle_);
    CHECK_IRET(iret);
    isinit_ = true;
    fprintf(stdout, "client (%p) init type = %d", &client_, client_.type);
    client_.data = this;
    log << "client (" << this << ") init " << endl; 
    return true;
}

void TCPClient::close(){
    if (!isinit_) return;
    uv_mutex_destroy(&write_mutex_handle_);
    uv_close((uv_handle_t*)&client_,afterClosed);
    log << "client (" << this << ") close" << endl;
    isinit_ = false;
}

bool TCPClient::run(int status) {
    log << "client ("<< this << ") running" << endl;
    int iret = uv_run(loop_, (uv_run_mode)status);
    CHECK_IRET(iret);
    return true;
}

bool TCPClient::setNoDelay(bool enable) {
    int iret = uv_tcp_nodelay(&client_, enable?1:0);
    CHECK_IRET(iret);
    return true;
}

bool TCPClient::setKeepAlive(int enable, unsigned int delay) {
    int iret = uv_tcp_keepalive(&client_, enable, delay);
    CHECK_IRET(iret);
    return true;
}

bool TCPClient::connect(const char* ip, int port) {
    close();
    init();
    connectip_ = ip;
    connectport_ = port;
    log << "client (" << this <<") start connect to server ("<< ip << ")" << endl;

    int iret = uv_thread_create(&connect_threadhandle_, connectThread, this);
    CHECK_IRET(iret);
    while (connectionstatus_ == CONNECT_DIS) {
        usleep((100)*1000);
    }

    return connectionstatus_ == CONNECT_FINISHI;
}

bool TCPClient::connect6(const char* ip, int port) {
    close();
    init();
    connectip_ = ip;
    connectport_ = port;
    log << "client (" << this <<") start connect to server ("<< ip << ")" << endl;

    int iret = uv_thread_create(&connect_threadhandle_, connectThread6, this);
    if (iret) {}
    CHECK_IRET(iret);
    while (connectionstatus_ == CONNECT_DIS) {
        usleep((100)*1000);
    }

    return connectionstatus_ == CONNECT_FINISHI;
}

void TCPClient::connectThread(void* arg) {
    TCPClient *pclient = (TCPClient*) arg;
    log << "client ("<<pclient<< ") connectThread start" << endl;
    struct sockaddr_in bind_addr;
    int iret = uv_ip4_addr(pclient->connectip_.c_str(), pclient->connectport_, &bind_addr);
    if (iret) {
        pclient->errmsg_ = getUVError(iret);
        log << pclient->errmsg_ << endl;
        return;
    }
    iret = uv_tcp_connect(&pclient->connect_req_, &pclient->client_, (const sockaddr*)&bind_addr, afterConnect);
    if (iret) {
        pclient->errmsg_ = getUVError(iret);
        log << pclient->errmsg_ << endl;
        return;
    }
    log << "client("<< pclient << ") connectThread end connect status " << pclient->connectionstatus_ << endl;
    pclient->run();
}

void TCPClient::connectThread6(void* arg) {
    TCPClient *pclient = (TCPClient*) arg;
    log << "client ("<<pclient<< ") connectThread6 start" << endl;
    struct sockaddr_in6 bind_addr;
    int iret = uv_ip6_addr(pclient->connectip_.c_str(), pclient->connectport_, &bind_addr);
    if (iret) {
        pclient->errmsg_ = getUVError(iret);
        log << pclient->errmsg_ << endl;
        return;
    }
    iret = uv_tcp_connect(&pclient->connect_req_, &pclient->client_, (const sockaddr*)&bind_addr, afterConnect);
    if (iret) {
        pclient->errmsg_ = getUVError(iret);
        log << pclient->errmsg_ << endl;
        return;
    }
    log << "client("<< pclient << ") connectThread6 end connect status " << pclient->connectionstatus_ << endl;
    pclient->run();
}

void TCPClient::afterConnect(uv_connect_t* handle, int status)
{
    log << "start after connect" << endl;
    TCPClient* pclient = (TCPClient*) handle->handle->data;
    if (status) {
        pclient->connectionstatus_ = status;
        pclient->errmsg_  = getUVError(status);
        log << "connect error: " << pclient->errmsg_ << endl;
    }
    int iret = uv_read_start(handle->handle, onAllocBuffer, afterClientRecv);
    if (iret) {
        pclient->errmsg_ = getUVError(iret);
        log << "uv_read_start error: "  << pclient->errmsg_ << endl;
        pclient->connectionstatus_ = CONNECT_ERROR;
    } else {
        pclient->connectionstatus_ = CONNECT_FINISHI;
    }
    log << "client (" << pclient << ") run" << endl;

}

int TCPClient::send(const char* data, std::size_t len) {
    if (!data ||len <= 0) {
        errmsg_ = "send data is null or len less than zero";
        return 0;
    }
    uv_mutex_lock(&write_mutex_handle_);
    if (writebuffer_.len < len) {
        writebuffer_.base = (char*)realloc(writebuffer_.base, len);
        writebuffer_.len = len;
    }
    memcpy(writebuffer_.base, data, len);
    uv_buf_t buf = uv_buf_init((char*)writebuffer_.base, len);
    int iret= uv_write(&write_req_, (uv_stream_t*)&client_, &buf, 1, afterSend);
    CHECK_IRET(iret);
    return true;
}

void TCPClient::setRecvCB(client_recvcb cb, void* userdata) {
    recvcb_ = cb;
    userdata = userdata;
}

void TCPClient::onAllocBuffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t *buf)
{
    if (!handle->data) return;
    TCPClient *client = (TCPClient*) handle->data;
    *buf = client->readbuffer_;
}

void TCPClient::afterClientRecv(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
    if (!handle->data) {
        return;
    }
    TCPClient *client = (TCPClient*)handle->data;
    if (nread <0) {
        if (nread == UV_EOF) 
            log << "server "<< handle <<" disconnect auto " << endl;
        else if (nread == UV_ECONNRESET)
            log << "server " << handle << " disconnect except" <<endl;
        else {
            client->errmsg_ = getUVError(nread);
            log << "serer " << handle << " disconnect exception: " << client->errmsg_ << endl;
        }
        uv_close((uv_handle_t*)handle, afterClosed);
        return;
    }
    if (nread > 0 && client->recvcb_) {
        client->recvcb_(buf->base, nread, client->userdata_);
    }
}

void TCPClient::afterSend(uv_write_t *req, int status) {
    TCPClient *client = (TCPClient*) req->handle->data;
    uv_mutex_unlock(&client->write_mutex_handle_);
    if (status < 0) {
        std::string msg = getUVError(status);
        log << "write error : " << msg << endl;
    }
}

void TCPClient::afterClosed(uv_handle_t *handle)
{
    log << "client " << handle << endl;
}

UV_NAMESPACE_END

