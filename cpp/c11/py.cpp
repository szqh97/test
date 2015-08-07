#include <iostream>
#include <python2.7/Python.h>

int main ( int argc, char *argv[] )
{
    Py_Initialize();
    PyRun_SimpleString("print \"Hello, C! -- from Python\"");
    Py_Finalize();

    return 0;
}			/* ----------  end of function main  ---------- */

