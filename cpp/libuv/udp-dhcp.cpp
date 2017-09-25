#include <iostream>
#include <uv.h>
#include <assert.h>

uv_loop_t *loop;
uv_udp_t send_socket;
uv_udp_t recv_socket;

void allock_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t* buf) {
    buf->base = malloc(suggested_size);
    buf->len = suggested_size;
}
