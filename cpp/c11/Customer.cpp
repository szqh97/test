#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <map>
#include <assert.h>

#include <boost/noncopyable.hpp>

//
// NOTE: this may be create thread error 
// tips about std::ref

class CustomerData: boost::noncopyable
{
    public:
    CustomerData():data_(new Map) {}

    int query(const std::string& customer, const std::string& stock) const;
    void updateMap(const std::string& customer, const std::string& stock, int value);

    private:
        typedef std::pair<std::string, int> Entry;
        typedef std::vector<Entry> EntryList;
        typedef std::map<std::string, EntryList> Map;
        typedef std::shared_ptr<Map> MapPtr;
        static std::mutex mutex_;
        MapPtr data_;

    private:
        void update(const std::string& customer, const EntryList& entries);

        static int findEntry(const EntryList& entries, const std::string& stock);

        MapPtr getData() const
        {
            std::lock_guard<std::mutex> lock(mutex_);
            return data_;
        }

};

std::mutex CustomerData::mutex_;

int CustomerData::findEntry(const EntryList& entries, const std::string& stock)
{
    for(int i = 0; i < entries.size(); ++i)
    {
        if (entries[i].first == stock)
            return entries[i].second;
    }
    return -1;
}

int CustomerData::query(const std::string& customer, const std::string& stock) const
{
    MapPtr data = getData();
    Map::const_iterator entries = data->find(customer);
    std::cout << "CustomerData::query " << customer << ", " << stock << std::endl;
    if(entries != data->end())
    {
        return findEntry(entries->second, stock);
    }
    else
        return -1;
}

void CustomerData::update(const std::string& customer, const EntryList& entries)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!data_.unique())
    {
        MapPtr newData(new Map(*data_));
        data_.swap(newData);
    }
    assert(data_.unique());
    (*data_)[customer] = entries;

}

void CustomerData::updateMap(const std::string& customer, const std::string& stock, int value)
{

    std::lock_guard<std::mutex> lock(mutex_);
    if (!data_.unique())
    {
        MapPtr newData(new Map(*data_));
        data_.swap(newData);
    }
    EntryList::iterator it = (*data_)[customer].begin();
    while (it != (*data_)[customer].end())
    {
        if (it->first == stock)
        {
            it->second = value;
            return;
        }
        ++it;
    }
    (*data_)[customer].push_back(std::pair<std::string, int>(stock, value));
    std::cout << "CustomerData::updateMap: " << customer << ", " << stock << ", " << value << std::endl;

}



void thread_func1(CustomerData& db)
{

    // this is for read
    
    std::cout << "query customer C1, stock s1 : " << db.query("C1", "s1") << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "query customer C1, stock s2 : " << db.query("C1", "s2") << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "query customer C2, stock s1 : " << db.query("C2", "s1") << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "query customer C2, stock s1 : " << db.query("C2", "s2") << std::endl;
}

void thread_func2(CustomerData& db, int value)
{
    // this is for write
    db.updateMap("C1", "s1", value);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    db.updateMap("C2", "s1", value);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    db.updateMap("C1", "s2", value);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    db.updateMap("C2", "s2", value);

    
}

int main ( int argc, char *argv[] )
{



    std::vector<std::thread> threads;
    CustomerData customer_db;
    for (int i = 0; i < 5; ++i)
    {
        std::thread t(thread_func1, std::ref(customer_db));
        threads.push_back(std::move(t));
    }

    for (int i = 0; i < 10; ++i)
    {
        std::thread t(thread_func2, std::ref(customer_db), i*19);
        threads.push_back(std::move(t));
    }

    for (std::vector<std::thread>::iterator it = threads.begin(); it != threads.end(); ++it)
    {
        it->join();
    }



    return 0;
}			/* ----------  end of function main  ---------- */
