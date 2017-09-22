#include <iostream>
#include <uv.h>
#include <string>
using namespace std;

uv_loop_t *loop;
const char* command;

void run_command(uv_fs_event_t* handle, const char* filename, int events, int status) {
    char path[1024];
    size_t size = 1023;
    uv_fs_event_getpath(handle, path, &size);
    path[size] = '\0';

    fprintf(stderr, "Change detected in %s\n", path);
    if (events & UV_RENAME)
        fprintf(stderr, "renamed\n");
    if (events & UV_CHANGE)
        fprintf(stderr, "changed\n");
    fprintf(stderr, " %s\n", filename ?filename: "");
    system(command);
}

int main(int argc, char** argv)
{
    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <command> <file1> [file2 ...]\n", argv[0] );
        return 1;
    }

    loop = uv_default_loop();
    command = argv[1];

    while (argc-- > 2) {
        fprintf(stderr, "Adding watch on %s\n", argv[argc]);

        uv_fs_event_t *fs_event_req = (uv_fs_event_t*) malloc(sizeof(uv_fs_event_t));
        uv_fs_event_init(loop, fs_event_req);
        uv_fs_event_start(fs_event_req, run_command, argv[argc], UV_FS_EVENT_RECURSIVE);
    }


    return uv_run(loop, UV_RUN_DEFAULT);

}
