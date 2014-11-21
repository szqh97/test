#include "Singleton.h"
#include <iostream>
Singleton* Singleton::_instance = 0;
Singleton::Singleton()
{
    std::cout << "Singleton::Single()" << endl;
}
Singleton* Singleton::getInstance()
{
    if (_instance == 0)
    {
        _instance = new Singleton();
    }
    return _instance;
}


