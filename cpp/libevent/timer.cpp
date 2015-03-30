#include <iostream>
#include <stdio.h>
#include <event.h>

using namespace std;
void onTime(int sock, short event, void *arg)
{
    cout << "Game over! " << endl;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    event_add((struct event*) arg, &tv);
}

int main ( int argc, char *argv[] )
{
    event_init();
    struct event evTime;
    evtimer_set(&evTime, onTime, &evTime);

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    event_add(&evTime, &tv);
    event_dispatch();
    return 0;
}	

