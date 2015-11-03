#include <iostream>
#include <stdio.h>
#include <stdint.h>
using namespace std;
int main(int argc, char *argv[])
{
    long long l = 111;
    printf("%lld\n", l);
    cout << __WORDSIZE << endl;
    return 0;
}
