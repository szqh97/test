#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace  boost::archive;
//// save pointer
class animal
{
public:
    animal () = default;
    animal (int legs): _legs(legs){}
    int legs()const {return _legs; }

    virtual ~animal (){}


private:
    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & _legs;
    }
    int _legs;
};

void save_p()
{

    std::ofstream file("/tmp/test_ser.txt");
    boost::archive::text_oarchive oa(file);
    animal *a = new animal(4);
    oa << a;
    std::cout << std::hex << a << std::endl;
    delete a;
}

void load_p()
{
    std::ifstream file("/tmp/test_ser.txt");
    boost::archive::text_iarchive ia(file);
    animal *a;
    std::cout << std::hex << a <<std::endl;
    ia >> a;
    std::cout << std::hex << a << std::endl;
    std::cout << std::dec << a->legs() << std::endl;
    delete a;

}

////// serialize class
class bird: public animal
{
public:
    bird() = default;
    bird(int legs, bool can_fly): animal(legs), _can_fly(can_fly){}
    bool can_fly()const {return _can_fly;}
private:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<animal>(*this);
        ar & _can_fly;

    }
    bool _can_fly;

};

BOOST_CLASS_EXPORT(bird)

void save_cls()
{
    std::ofstream file("/tmp/ser_cls.txt");
    boost::archive::text_oarchive oa(file);
    bird penguin(2, false);
    oa << penguin;

    animal *a = new bird(2, false);
    oa << a;
    delete a;
}

void load_cls()
{
    std::ifstream file("/tmp/ser_cls.txt");
    boost::archive::text_iarchive ia (file);
    bird peng;
    ia >> peng;
    std::cout << peng.legs() << "  " << peng.can_fly() << std::endl;

    animal *a ;
    ia >> a;
    std::cout << a->legs() << " xxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
    delete a;
}

int main()
{
    save_p();
    load_p();

    save_cls();
    load_cls();
    
    return 0;
}
