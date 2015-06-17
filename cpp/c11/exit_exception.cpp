#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
#include <boost/noncopyable.hpp>

void someFunctionCallExit()
{
    exit(1);
}

class GlobalObject: boost::noncopyable
{
    public:
        void doit()
        {
            std::lock_guard<std::mutex> lock(mutex_);
            someFunctionCallExit();
        }
        ~GlobalObject()
        {
            printf("GlobalObject::~GlobalObject() \n");
            std::lock_guard<std::mutex> lock(mutex_);
            printf("GlobalObject::~GlobalObject() cleaning up\n");

        }
    private:
        std::mutex mutex_;
};

GlobalObject g_obj;
int main ( int argc, char *argv[] )
{

    g_obj.doit();

    return 0;
}			/* ----------  end of function main  ---------- */


