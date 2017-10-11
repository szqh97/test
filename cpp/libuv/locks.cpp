#include <iostream>
#include <uv.h>
using namespace std;

uv_barrier_t blocker;
uv_rwlock_t numlock;
int shared_num;

void reader(void *n) {
    int num = *(int*)n;
    int i;
    for (i = 0; i < 20; ++i) {
        uv_rwlock_rdlock(&numlock);
        cout << "reader " << num << ": acquired lock" <<   endl;
        cout << "reader " << num << ": shared num = " << shared_num << endl;
        uv_rwlock_rdunlock(&numlock);
        cout << "reader " << num << ": released lock" << endl;
    }
    uv_barrier_wait(&blocker);
}

void writer(void *n) {
    int num = *(int*)n;
    int i ;
    for (i = 0; i < 20; ++i) {
        uv_rwlock_wrlock(&numlock);
        cout << "writer " << num << " :acquired lock" << endl;
        shared_num++;
        cout << "writer " << num << " :incremented shared num = " << shared_num << endl;
        uv_rwlock_wrunlock(&numlock);
        cout << "writer " << num  << "released lock" << endl;
    }
    uv_barrier_wait(&blocker);
}

int main()
{
    uv_barrier_init(&blocker, 4);

    shared_num = 0;
    uv_rwlock_init(&numlock);

    uv_thread_t threads[3];
    int thread_num[] = {1,2,1};
    uv_thread_create(&threads[0], reader, &thread_num[0]);
    uv_thread_create(&threads[1], reader, &thread_num[1]);

    uv_thread_create(&threads[2], writer, &thread_num[2]);

    uv_barrier_wait(&blocker);
    uv_barrier_destroy(&blocker);

    uv_rwlock_destroy(&numlock);

    return 0;
}
