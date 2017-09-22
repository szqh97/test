#include <iostream>
#include <uv.h>
int main()
{
    uv_loop_t *loop = new (uv_loop_t);
    uv_loop_init(loop);

    std::cout << "now quit" << std::endl;
    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    delete loop;
    return 0;
}

