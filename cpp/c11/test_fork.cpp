#include <iostream>
#include <unistd.h>
       #include <sys/types.h>
       #include <sys/wait.h>

using namespace std;

int main ( int argc, char *argv[] )
{
    pid_t fpid;
    fpid = fork();
    if (fpid < 0)
        cerr<< "error" << endl;
    else if (fpid == 0)
    {
        char *p = new char[1024];
        
        cout << "son" << endl;
        sleep(1);
    }
    else {
        int i =0;
        sleep(2);
        waitpid(fpid, &i, 0);
        cout << "father" << endl;
    }
    return 0;
}			/* ----------  end of function main  ---------- */

