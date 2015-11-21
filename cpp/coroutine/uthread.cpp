
#include "uthread.h"

int uthread_create(schedule_t& schedule, Func func, void* arg)
{
    int id = 0;
    int threadnum = schedule.threads.size();
    
    for (id = 0; id < threadnum; ++id)
    {
        if (schedule.threads[id].state == FREE)
        {
            break;
        }
    }

    if (id == threadnum)
    {
        uthread_t _thread;
        schedule.threads.push_back(_thread);
    }

    uthread_t *t = &(schedule.threads[id]);
    t->state = RUNNABLE;
    t->func = func;
    t->arg = arg;

    return id;
}

static void uthread_body(schedule_t* ps)
{
    int id = ps->running_thread;
    if (-1 != id)
    {
        uthread_t* t = &(ps->threads[id]);
        t->func(t->arg);
        t->state = FREE;
        ps->running_thread = -1;
    }
}

void uthread_yield(schedule_t& schedule)
{
    if (-1 != schedule.running_thread)
    {
        uthread_t* t = &(schedule.threads[schedule.running_thread]);
        t->state = SUSPEND;
        schedule.running_thread = -1;

        swapcontext(&(t->ctx), &(schedule.main));
    }
}

void uthread_resume(schedule_t& schedule, int id)
{
    if (id < 0 || (unsigned long)id >= schedule.threads.size())
    {
        return ;
    }
    uthread_t* t  = &(schedule.threads[id]);
    switch(t->state)
    {
        case RUNNABLE:
            getcontext(&(t->ctx));
            t->ctx.uc_stack.ss_sp = t->stack;
            t->ctx.uc_stack.ss_size = DEFAULT_STACK_SIZE;
            t->ctx.uc_stack.ss_flags = 0;
            t->state = RUNNING;
            schedule.running_thread = id;
            makecontext(&(t->ctx), (void(*) (void)) (uthread_body), 1, &schedule);
            // NOT NEED BREAK!!!
        case SUSPEND:
            swapcontext(&(schedule.main), &(t->ctx));
            break;
        default: ;

    }
}

int schedule_finished(const schedule_t& schedule)
{
    if (-1 != schedule.running_thread)
    {
        return 0;
    }
    else
    {
        for(auto i = 0; i < schedule.threads.size(); ++i)
        {
            if (FREE != schedule.threads[i].state)
            {
                return 0;
            }
        }
    }
    return 1;
}
