#include <boost/archive/text_oarchive.hpp>
#include <iostream> 
#include <fstream> 
using namespace std;

void save() 
{ 
  std::ofstream f("./archive.txt", ios::out | ios::binary);
  boost::archive::text_oarchive oa(f); 
  std::string s = "Hello World!\n"; 
  oa << s; 
} 

int main()
{
    save();
}
