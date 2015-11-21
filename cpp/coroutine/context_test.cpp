#include <ucontext.h>
#include <stdio.h>
void func1(void * arg)
{
    puts("1");
    puts("11");
    puts("111");
    puts("1111");
}

void context_test()
{
    char stack[1024*128];
    ucontext_t child_c, main_c;

    getcontext(&child_c);
    child_c.uc_stack.ss_sp = stack;
    child_c.uc_stack.ss_size = sizeof(stack);
    child_c.uc_stack.ss_flags = 0;
    child_c.uc_link = &main_c;

    makecontext(&child_c, (void(*)(void))func1, 0);

    swapcontext(&main_c, &child_c);
    puts("main");
}

int main(int argc, char *argv[])
{
    context_test();
    return 0;
}
