#include <semaphore.h> 
#include <semaphore.h>
#include <pthread.h>

#include <iostream>

using namespace std;
sem_t beginSemaArr[500];
long global_cnt = 0;

void *threadAddFunc(void *param)
{
    long thread_id = *(long*) param;
    cout << "thread_id" << thread_id << endl;
    for(;;)
    {
        sem_wait(&beginSemaArr[thread_id]);
        for (int i = 0; i < 10000; i++)
            global_cnt++;
        sem_post(&beginSemaArr[thread_id]);

    }

}

int main ( int argc, char *argv[] )
{
    for (int i = 0; i < 500; ++i)
    {
        if (sem_init(&beginSemaArr[i], 0, 0) == -1)
        {
            cerr << "init sem error" << endl;
        }
            pthread_t ntid;
            int err = pthread_create(&ntid, NULL, threadAddFunc, (void*)&i);
            pthread_detach(ntid);
    }

    return 0;
}			/* ----------  end of function main  ---------- */
