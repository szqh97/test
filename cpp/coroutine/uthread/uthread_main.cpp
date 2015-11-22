#include "uthread.h"
#include <stdio.h>
void func2(void* arg)
{
    puts("func2");
    puts("func2");
    uthread_yield(*(schedule_t*) arg);
    puts("func2");
    puts("func2");
}

void func3(void* arg)
{
    puts("func3");
    puts("func3");
    puts("func3");
    uthread_yield(*(schedule_t*)arg);
    puts("func3");
    puts("func3");
}

void schedule_test()
{
    schedule_t s;
    int tid1 = uthread_create(s, func3, &s);
    int tid2 = uthread_create(s, func2, &s);

    while(!schedule_finished(s))
    {
        uthread_resume(s, tid2);
        uthread_resume(s, tid1);
    }
    puts("main over");
}



int main()
{
    schedule_test();
    return 0;
}
