#ifndef  _Singleton_H_
#define  _Singleton_H_
#include <iostream>
using namespace std;

class Singleton
{
    public:
        static Singleton* getInstance();

    private:
        static Singleton* _instance;
        Singleton ();     

};


#endif 
