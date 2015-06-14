#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include <map>
#include <thread>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/bind.hpp>
using namespace boost;

class Mutex: boost::noncopyable
{
public: 
    Mutex(){m_.lock();}
    ~Mutex(){m_.unlock();}
private:
    std::mutex m_;
};

class Stock: boost::noncopyable
{
public:
    Stock(const std::string& name): name_(name)
    {

        std::cout << "constructor stock[ "<< name_ << " ]" << std::endl;
    }
    virtual ~Stock()
    {
        std::cout << "destructor stock[ " << name_ << " ]" << std::endl;
    }
    std::string Key()const  {return name_; }
private:
    std::string name_;

};

namespace version1
{

    class StockFactory:boost::noncopyable
    {

    public:
        std::shared_ptr<Stock> get_stock(const std::string& name)
        {
            std::shared_ptr<Stock> pStock;
            {
                Mutex m;
                pStock = stocks_[name];
            }
            if (!pStock)
            {
                pStock.reset(new Stock(name));
            }
            return pStock;
            
        }
    private:
        std::map<std::string, std::shared_ptr<Stock>> stocks_;
    };
    

}

namespace version2 
{
    class StockFactory:boost::noncopyable
    {

    public:
        std::shared_ptr<Stock> get_stock(const std::string& name)
        {
            std::shared_ptr<Stock> pStock;
            Mutex m;
            std::weak_ptr<Stock> wkStock = stocks_[name];
            pStock = wkStock.lock();
            if (!pStock)
            {
                pStock.reset(new Stock(name));
                wkStock = pStock;
            }
            return pStock;
            
        }
    private:
        std::map<std::string, std::weak_ptr<Stock>> stocks_;
    };
    


}

namespace version3 
{
    class StockFactory:boost::noncopyable
    {

    public:
        std::shared_ptr<Stock> get_stock(const std::string& name)
        {
            std::shared_ptr<Stock> pStock;
            Mutex m;
            std::weak_ptr<Stock> wkStock = stocks_[name];
            pStock = wkStock.lock();
            if (!pStock)
            {
                //pStock.reset(new Stock(name), std::bind(&StockFactory::deleteStock, _1, this));
                pStock.reset(new Stock(name),boost::bind(&StockFactory::deleteStock,this, _1));
                wkStock = pStock;
            }
            return pStock;
            
        }
    private:
        std::map<std::string, std::weak_ptr<Stock>> stocks_;
        void deleteStock(Stock* stock)
        {
            if (stock)
            {
                Mutex m_;
                stocks_.erase(stock->Key());
            }
            delete stock;
        }
    };
    


}

namespace version4 
{
    class StockFactory: public boost::enable_shared_from_this<StockFactory>, boost::noncopyable
    {

    public:
        shared_ptr<Stock> get_stock(const std::string& name)
        {
            shared_ptr<Stock> pStock;
            Mutex m;
            weak_ptr<Stock> wkStock = stocks_[name];
            pStock = wkStock.lock();
            if (!pStock)
            {
                //pStock.reset(new Stock(name), std::bind(&StockFactory::deleteStock, _1, this));
                pStock.reset(new Stock(name),boost::bind(&StockFactory::deleteStock, shared_from_this(), _1));
                wkStock = pStock;
            }
            return pStock;
            
        }
    private:
        std::map<std::string,weak_ptr<Stock>> stocks_;
        void deleteStock(Stock* stock)
        {
            if (stock)
            {
                Mutex m_;
                stocks_.erase(stock->Key());
            }
            delete stock;
        }
    };
    


}

namespace version5
{
    class StockFactory: public boost::enable_shared_from_this<StockFactory>, boost::noncopyable
    {
        public:
            shared_ptr<Stock> get_stock(const std::string& key)
            {
                shared_ptr<Stock> pStock;
                Mutex m_;
                weak_ptr<Stock>& wkStock = stocks_[key];
                pStock = wkStock.lock();
                if (!pStock)
                {
                    pStock.reset(new Stock(key), 
                            boost::bind(&StockFactory::weakDeleteCallback,
                            boost::weak_ptr<StockFactory>(shared_from_this()),
                            _1));
                }
            }
        private:
            std::map<std::string, weak_ptr<Stock> > stocks_;
            static void weakDeleteCallback(const boost::weak_ptr<StockFactory>& wkFactory, Stock* stock)
            {
                shared_ptr<StockFactory> factory(wkFactory.lock());
                if (factory)
                {
                    factory->removeStock(stock);
                }
                delete stock;
            }

            void removeStock(Stock* stock)
            {
                if (stock)
                {
                    Mutex m_;
                    stocks_.erase(stock->Key());
                }
            }
    };

    void testLongLifeFactory()
    {

        shared_ptr<StockFactory> factory(new StockFactory);
        {
            shared_ptr<Stock> s1 = factory->get_stock("IBM");
            shared_ptr<Stock> s2 = factory->get_stock("Mic");
        }
    }

    void testShortLifeFactory()
    {
        shared_ptr<Stock> stock;
        {
            shared_ptr<StockFactory> factory (new StockFactory);
            stock = factory->get_stock("IBM");
            shared_ptr<Stock> s2 = factory->get_stock("TEST");

        }
    }
}

#define FACTORYVERSION version3
void func()
{
    FACTORYVERSION::StockFactory sf3 ;
    std::shared_ptr<Stock> s3 = sf3.get_stock("145");
    std::shared_ptr<Stock> s3w = sf3.get_stock("145");
 
}

void func_v4()
{
    shared_ptr<version4::StockFactory> sf(new version4::StockFactory);
    shared_ptr<Stock> s3 = sf->get_stock("test");
    shared_ptr<Stock> s4 = sf->get_stock("test");
}
int main ( int argc, char *argv[] )
{
//    version1::StockFactory sf1 ;
//    std::shared_ptr<Stock> s1 = sf1.get_stock("145");
//    std::shared_ptr<Stock> s1w = sf1.get_stock("145");
//
//    version2::StockFactory sf2 ;
//    std::shared_ptr<Stock> s2 = sf2.get_stock("145");
//    std::shared_ptr<Stock> s2w = sf2.get_stock("145");
//
//    version2::StockFactory sf3 ;
//    std::shared_ptr<Stock> s3 = sf3.get_stock("145");
//    std::shared_ptr<Stock> s3w = sf3.get_stock("145");

    for(int i =0; i < 10; ++i)
    {
        std::thread t(func_v4);
        t.join();
    }

    version5::testLongLifeFactory();
    version5::testShortLifeFactory();
    return 0;

}			/* ----------  end of function main  ---------- */
