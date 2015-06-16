#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main ( int argc, char *argv[] )
{
    int oldfd;
    oldfd = open("test.log", O_RDWR | O_CREAT, 0644);
    dup2(oldfd, 2);
    cerr << "fsfsdf's'fsd'f'sd'fsd'f's'f'esfg' " << endl;
    close(oldfd);
    cerr << "testest" << endl;


    return 0;
}			/* ----------  end of function main  ---------- */

