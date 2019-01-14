#include <iostream>
#include <webp/encode.h>
using namespace std;
int main(int argc, char* argvs[])
{
    if (argc !=2) {
        cout << "usage: "<< argvs[0] << " orgfile " << endl;
        return -1;
    }
    string dstfile(argvs[1]);
    dstfile += ".webp";
    

    return 0;
}
