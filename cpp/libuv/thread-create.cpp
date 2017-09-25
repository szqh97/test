#include <iostream>
#include <uv.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void hare(void *arg) {
    int tracklen = *((int*) arg);
    while (tracklen) {
        tracklen--;
        sleep(1);
        cerr << "Hare ran another step" << endl;
    }
    cout << "Hare done running." << endl;
}

void tortoise(void *arg) {
    int tracklen = *((int*)arg);
    while(tracklen) {
        tracklen--;
        cerr << "Tortoise ran another step" << endl;
        sleep(3);
    }
    cerr << "Totoise done running" << endl;
}
int main()
{
    int tracklen = 10;
    uv_thread_t hare_id;
    uv_thread_t tortoise_id;
    uv_thread_create(&hare_id, hare, &tracklen);
    uv_thread_create(&tortoise_id, tortoise, &tracklen);

    uv_thread_join(&hare_id);
    uv_thread_join(&tortoise_id);

    return 0;
}
