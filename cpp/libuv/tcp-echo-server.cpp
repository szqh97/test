#include <iostream>
#include <uv.h>
#include <string>
using namespace std;

#define DEFAULT_PORT 7000
#define DEFAULT_BACKLOG 128

uv_loop_t* loop;
struct sockaddr_in addr;

typedef struct  {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

void free_write_req(uv_write_t* req) {
    write_req_t* wr = (write_req_t*) req;
    free (wr->buf.base);
    free(wr);
}

void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
    buf->base = (char*) malloc(suggested_size);
    buf->len = suggested_size;
}

void echo_write(uv_write_t* req, int status) {
    if (status) {
        cerr << "write error " << uv_strerror(status) << endl;
    }
    free_write_req(req);
}

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t* buf)
{
    if (nread> 0) {
        write_req_t *req = new(write_req_t);
        req->buf = uv_buf_init(buf->base, nread);
        uv_write((uv_write_t*) req, client, &req->buf, 1, echo_write);
        return;
    }
    if (nread < 0) {
        if (nread != UV_EOF) {
            cerr << "Read error "<< uv_err_name(nread) << endl;
        }
        uv_close((uv_handle_t*)client, NULL);
    }
    free(buf->base);
}


void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        cerr << "New connection error " << uv_strerror(status)<<endl;
        return;
    }

    uv_tcp_t *client = new (uv_tcp_t);
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        uv_read_start((uv_stream_t*)client, alloc_buffer, echo_read);
    } else {
        uv_close((uv_handle_t*)client, NULL);
    }
}

int main()
{
    loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);

    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    int r = uv_listen((uv_stream_t*)&server, DEFAULT_BACKLOG, on_new_connection);
    if (r) {
        std::cerr<< "Listen error " << uv_strerror(r) << std::endl;
        return 1;
    }

    return uv_run(loop, UV_RUN_DEFAULT);

}
