#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sys/time.h>
#include <stdint.h>
using namespace std;

struct live_timeval
{
    uint64_t tv_sec;
    uint64_t tv_usec;
};
template<typename T> 
int live_time_cmp(const T &t1, const T &t2);
template<typename T> 
int live_time_cmp(const T &t1, const T &t2)
{
    if (t1.tv_sec < t2.tv_sec)
        return -1;
    if (t1.tv_sec == t2.tv_sec && t1.tv_usec < t2.tv_usec)
        return -1;
    if (t1.tv_sec == t2.tv_sec && t1.tv_usec == t2.tv_usec)
        return 0;
    return 1;
}

#if 0

int main ( int argc, char *argv[] )
{
    timeval tv1, tv2;
    struct live_timeval lt1, lt2;
    lt1.tv_sec = tv1.tv_sec;
    lt1.tv_usec = tv1.tv_usec;

    lt2.tv_sec = tv2.tv_sec;
    lt2.tv_usec = tv2.tv_usec;
    gettimeofday(&tv1, NULL);
    gettimeofday(&tv2, NULL);
    cout << live_time_cmp(tv1, tv2) << endl;
    cout << live_time_cmp(tv1, tv1) << endl;
    cout << live_time_cmp(tv2, tv1)<< endl;;

    cout << live_time_cmp(lt1, lt2) << endl;
    cout << live_time_cmp(lt1, lt1) << endl;
    cout << live_time_cmp(lt2, lt1) << endl;
    return 0;
}			/* ----------  end of function main  ---------- */
#endif
