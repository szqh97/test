#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using namespace boost::archive;

///////////// test oarchive
void test_text_oarchive()
{
    boost::archive::text_oarchive oa(std::cout);
    int i = 100;
    oa << i;
    std::string str = "test me";
    oa << str;
}

////////// test save and then load from archive
void save()
{
    std::ofstream file("/tmp/test_ser.txt");
    boost::archive::text_oarchive oa(file);
    int i = 100;
    oa << i ;
    std::string str = "test me";
    oa << str;
}

void load()
{
    std::ifstream file("/tmp/test_ser.txt");
    boost::archive::text_iarchive ia(file);
    int i = 0;
    ia >> i;
    std::cout << i << std::endl;
    std::string s;
    ia >> s;
    std::cout << s << std::endl;
}

/////////////////// serializating with a stringstream.
std::stringstream ss;
void save_sstream()
{
    boost::archive::text_oarchive oa(ss);
    int i = 1 ;
    oa << i;
    std::string s = "test me";
    oa << s;
}

void load_sstream()
{
    boost::archive::text_iarchive ia(ss);
    int i = 0;
    std::string s;
    ia >> i >> s;

    std::cout << i << std::endl << s << std::endl;
}

////////// serilizating user-defined types with a member function

class animal
{
public:
    animal () = default;
    animal (int legs):_legs(legs){};
    int legs() const {return _legs;}
    virtual ~animal (){};

private:
    friend class boost::serialization::access;
    template < typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & _legs;
    }
    int _legs;
};

void save_cls()
{

    std::ofstream file("/tmp/save_cls.txt");
    boost::archive::text_oarchive oa (file);
    animal a(5);
    oa << a;
}

void load_cls()
{
    std::ifstream file("/tmp/save_cls.txt");
    boost::archive::text_iarchive ia (file);
    animal a;
    ia >> a;
    std::cout << "test : " << a.legs() << std::endl;
}

///  serializing with a free-standing function
struct animal2 
{
    int _legs;
    animal2() = default;
    animal2(int l): _legs(l){}
    int legs()const {return _legs;}
};

template <typename Archive> 
void serialize(Archive &ar, animal2& a, const unsigned int version)
{
    ar & a._legs;
}


void save_free()
{
    std::ofstream file ("/tmp/save_free.txt");
    boost::archive::text_oarchive oa(file);
    animal2 a (4);
    oa << a ;
}

void load_free()
{
    std::ifstream file ("/tmp/save_free.txt");
    boost::archive::text_iarchive ia(file);
    animal2 a ;
    ia >> a;
    std::cout << a.legs() << std::endl;
}

int main(int argc, char *argv[])
{
    test_text_oarchive();
    save();
    load();

    save_sstream();
    load_sstream();

    save_cls();
    load_cls();

    save_free();
    load_free();
    return 0;
}

