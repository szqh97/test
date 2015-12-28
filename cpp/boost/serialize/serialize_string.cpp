#include "boost/archive/text_oarchive.hpp"
#include <iostream> 
#include <fstream> 

void save() 
{ 
  std::ofstream file("archive.txt"); 
  boost::archive::text_oarchive oa(file); 
  std::string s = "Hello World!\n"; 
  oa << s; 
} 

int main()
{
    save();
}
