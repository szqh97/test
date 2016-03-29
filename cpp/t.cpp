#include <iostream>
#include <stdint.h>
using namespace std;
#if 0
#undef int32_t
typedef int int32_t;
#ifdef int64_t
#undef int64_t
typedef long long            int64_t;
#endif
#endif

int main(int argc, char *argv[])
{
    
    int32_t t = 111;
    cout << t << endl;
    int64_t k = 1;
    cout << k << endl;
    cout << __SIZEOF_LONG_LONG__ << endl;
    cout << __SIZEOF_LONG__ << endl;
    cout << sizeof(int64_t) << endl;

    return 0;
}
