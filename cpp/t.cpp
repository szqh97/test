#include <iostream>
#include <stdint.h>
#include <string>
using namespace std;
#if 0
#undef int32_t
typedef int int32_t;
#ifdef int64_t
#undef int64_t
typedef long long            int64_t;
#endif
#endif

const char *T = "/im/autoreply";
const std::string AUTOREPLY_PREFIX    = "/im/autoreply";
const std::string AUTOREPLY_STATUS    = AUTOREPLY_PREFIX + "/status";
const std::string AUTOREPLY_CONTENT   = AUTOREPLY_PREFIX + "/content";
int main()
{
    
    int32_t t = 111;
    cout << t << endl;
    int64_t k = 1;
    cout << k << endl;
    cout << __SIZEOF_LONG_LONG__ << endl;
    cout << __SIZEOF_LONG__ << endl;
    cout << sizeof(int64_t) << endl;
    cout << sizeof(T) << endl;
    cout << strlen(T) << endl;
    cout << AUTOREPLY_PREFIX.length() << endl;

    return 0;
}
