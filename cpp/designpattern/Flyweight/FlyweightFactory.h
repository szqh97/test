#ifndef  _FlyweightFactory_H_
#define  _FlyweightFactory_H_
#include <string>
#include <vector>
#include "Flyweight.h"

using namespace std;

class FlyweightFactory
{
    public:
        FlyweightFactory ();  
        ~FlyweightFactory ();  
        Flyweight* GetFlyweight(const string& key);


    private:
        vector<Flyweight*> _fly;

}; 

#endif  
