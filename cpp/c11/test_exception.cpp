#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <exception>
#include <mutex>


using namespace std;
std::vector<std::exception_ptr> g_exceptions;
std::mutex g_mutex;

void throw_functions(const string &strerr)
{
    throw std::exception();
}

void func()
{
    try
    {
        throw_functions("some errors occurred!");
    }
    catch (...)
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        cerr <<" error" << endl;
    }
}


int main ( int argc, char *argv[] )
{

    return 0;
}			/* ----------  end of function main  ---------- */

