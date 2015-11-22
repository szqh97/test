#ifndef UTHREAD_H_ZVODHMAG
#define UTHREAD_H_ZVODHMAG
#include <ucontext.h>
#include <vector>

const int DEFAULT_STACK_SIZE = 1024*128;

enum ThreadState
{
    FREE=0,
    RUNNABLE,
    RUNNING,
    SUSPEND,
};


typedef void (*Func)(void* arg);


struct uthread_t
{
    ucontext_t ctx;
    Func func;
    void* arg;
    enum ThreadState state;
    char stack[DEFAULT_STACK_SIZE];
};

struct schedule_t
{
    ucontext_t main;
    int running_thread;
    std::vector<uthread_t> threads;

    schedule_t(): running_thread(-1){}
};

static void uthread_body(schedule_t* ps);

int uthread_create(schedule_t& schedule, Func func, void *arg);

void uthread_yield(schedule_t& schedule);

void uthread_resume(schedule_t& schedule, int id);

int schedule_finished(const schedule_t& schedule);

#endif /* end of include guard: UTHREAD_H_ZVODHMAG */
