#include <iostream>
#include <sys/time.h>
int main()
{
    //std::cout << std::chrono::system_clock::now() << std::endl;
	 struct timeval tval;
	 uint64_t ret_tick;
	 
	 gettimeofday(&tval, NULL);
	 
	 ret_tick = tval.tv_sec * 1000L + tval.tv_usec / 1000L;
	std::cout << ret_tick << std::endl;
	std::cout << time(NULL)<< std::endl;
    return 0;
}
