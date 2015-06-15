#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
#include <set>
class Request;
std::mutex mutex_i;
std::mutex mutex_r;
class Inventory
{
    public:
        void add(std::shared_ptr<Request> req)
        {
            std::lock_guard<std::mutex> lock(mutex_r);
            requests_.insert(req);
        }

        void remove(std::shared_ptr<Request> req) // __attribute__((oninline))
        {
            std::lock_guard<std::mutex> lock(mutex_r);
            requests_.erase(req);
        }

        void printAll() const;
    private:
        //std::mutex mutex_;
        std::set<std::shared_ptr<Request> > requests_;
};



Inventory g_inventory;

class Request: public std::enable_shared_from_this<Request>
{
    public:
        void process()
        {
            std::lock_guard<std::mutex> lock(mutex_i);
            g_inventory.add(getRequest());
        }
        
        ~Request() __attribute__((noinline))
        {
            std::lock_guard<std::mutex> lock(mutex_i);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            g_inventory.remove(getRequest());
        }
        
        std::shared_ptr<Request> getRequest()
        {
            return shared_from_this();
        }

        void print() const  __attribute__((noinline))
        {
            std::lock_guard<std::mutex> lock(mutex_r);
            std::cout << "in Requtest::print()" << std::endl;
        }

    private:
        //std::mutex mutex_;
};

void Inventory::printAll() const
{
    std::lock_guard<std::mutex> lock(mutex_r);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for(std::set<std::shared_ptr<Request> >::iterator it = requests_.begin(); it != requests_.end(); ++it)
    {
        (*it)->print();
    }
    std::cout << "Inventory::printAll() unlocked" << std::endl;
}
void ThreadFunc()
{
    std::shared_ptr<Request> req(new Request);
    req->process();
}

int main ( int argc, char *argv[] )
{
   // std::thread t(ThreadFunc);
    //std::this_thread::sleep_for(std::chrono::milliseconds(5 *1000));
    ThreadFunc();
    //g_inventory.printAll();
    //t.join();


    return 0;
}			/* ----------  end of function main  ---------- */
