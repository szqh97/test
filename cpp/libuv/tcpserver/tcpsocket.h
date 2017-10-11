#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_ value
#include <uv.h>
#include <string>
#include <iostream>
#include <map>
#include <list>
#include <unistd.h>
#include <string.h>
#define UV_NAMESPACE_BEGIN namespace uv {
#define UV_NAMESPACE_END };
#define BUFFERSIZE (1024*1024)

UV_NAMESPACE_BEGIN
typedef void (*newconnect)(int clientid);
typedef void (*server_recvcb)(int clientid, const char* buf, int bufsize);
typedef void (*client_recvcb)(const char* buf, int bufsize, void* userdata);

class TCPServer;
class ClientData {
    public:
        ClientData(int clientid):client_id(clientid), recvcb_(nullptr) {
            client_handle = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
            client_handle->data = this;
            readbuffer = uv_buf_init((char*)malloc(BUFFERSIZE), BUFFERSIZE);
            writebuffer = uv_buf_init((char*)malloc(BUFFERSIZE), BUFFERSIZE);
        }

        virtual ~ClientData(){
            free(readbuffer.base);
            readbuffer.base = nullptr;
            readbuffer.len = 0;

            free(writebuffer.base);
            writebuffer.base = nullptr;
            writebuffer.len = 0;

            free(client_handle);
            client_handle = nullptr;

        }

        int client_id;
        uv_tcp_t* client_handle;
        TCPServer* tcp_server;
        uv_buf_t readbuffer; //接收数据的buf
        uv_buf_t writebuffer; // 写数据的buf
        uv_write_t write_req;
        server_recvcb recvcb_; //接收数据回调给用户的函数
};

class TCPServer {
    public:
        TCPServer(uv_loop_t* loop = uv_default_loop());
        virtual ~TCPServer();
        static void startLog(const char* logpath = nullptr);
    public:
        bool start(const char* ip, int port);
        bool start6(const char* ip, int port);
        void close();

        bool setNoDelay(bool enable);
        bool setKeepAlive(int enable, unsigned int delay);

        const char* getLastErrMsg() const {
            return errmsg_.c_str();
        }

        virtual int send(int clientid, const char* data, std::size_t len);
        virtual void setNewConnectCB(newconnect cb);
        virtual void setRecvCB(int clientid, server_recvcb cb);

    protected:
        int getAvailableClientId() const;
        bool deleteClient(int clientid);

        static void afterServerRecv(uv_stream_t *client, ssize_t nread, const uv_buf_t* buf);
        static void afterSend(uv_write_t *req, int status);
        static void onAllocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
        static void afterServerClosed(uv_handle_t *handle);
        static void afterClientClosed(uv_handle_t *handle);
        static void acceptConnection(uv_stream_t *server, int status);

    private:
        bool init();
        bool run(int status = UV_RUN_DEFAULT);
        bool bind(const char* ip, int port);
        bool bind6(const char* ip, int port);
        bool listen(int backlog=1024);

    private:
        uv_tcp_t server_; // 服务器连接
        std::map<int, ClientData*> clients_list_; // 子客户端连接
        uv_mutex_t mutex_handle_;
        uv_loop_t* loop_;
        std::string errmsg_;
        newconnect newconnectcb_;
        bool isinit_;
};

class TCPClient {
    public:
        TCPClient(uv_loop_t *loop=uv_default_loop());
        virtual ~TCPClient();
        static void startLog(const char* logpath = nullptr);

    public:
        virtual bool connect(const char* ip, int port);
        virtual bool connect6(const char* ip, int port);
        virtual int send(const char* data, std::size_t len);
        virtual void setRecvCB(client_recvcb cb, void* userdata);
        void close();

        bool setNoDelay(bool enable);
        bool setKeepAlive(int enable, unsigned int delay);
        const char* getLastErrMsg() const { return errmsg_.c_str(); }
        
    protected:
        static void afterConnect(uv_connect_t* handle, int status);
        static void afterClientRecv(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
        static void afterSend(uv_write_t *req, int status);
        static void onAllocBuffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
        static void afterClosed(uv_handle_t* handle);

        static void connectThread(void* arg);
        static void connectThread6(void* arg);

        bool init();
        bool run(int status = UV_RUN_DEFAULT);

    private:
        enum {
            CONNECT_TIMEOUT,
            CONNECT_FINISHI,
            CONNECT_ERROR,
            CONNECT_DIS,
        };
        uv_tcp_t client_;
        uv_loop_t *loop_;
        uv_write_t write_req_; //写时请求
        uv_connect_t connect_req_;
        uv_thread_t connect_threadhandle_;
        std::string errmsg_;
        uv_buf_t readbuffer_;
        uv_buf_t writebuffer_;
        uv_mutex_t write_mutex_handle_;

        int connectionstatus_;
        client_recvcb recvcb_;
        void* userdata_;
        std::string connectip_;
        int connectport_;
        bool isinit_;
};


UV_NAMESPACE_END

#endif /* ifndef TCPSOCKET_H_ */
