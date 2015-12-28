#include <iostream>
#include <map>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/foreach.hpp>
#include <boost/any.hpp>
#include <boost/serialization/vector.hpp>
using namespace std;

int main()
{
    map<int, int> mymap;
    mymap.insert(pair<int, int>(1,2));
    mymap.insert(pair<int, int>(2,2));
    mymap.insert(pair<int, int>(3,2));
    return 0;
}
