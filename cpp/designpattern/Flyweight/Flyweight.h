
#ifndef  _Flyweight_H_
#define  _Flyweight_H_
#include <string>
using namespace std;

class Flyweight
{
    public:
        virtual ~Flyweight ();  
        virtual void Operation(const string& extrinsicState);
        string GetIntrinsicState();
    protected:
        Flyweight (const string& intrinsicState);    
    private:
        string _instrisicState;

}; 


class ConcreteFlyweight: public Flyweight
{
    public:
        ConcreteFlyweight (const string& intrinsicState);;      
        ~ConcreteFlyweight ();      
        void Operation(const string& extrinsicState);


    protected:

    private:

}; /* -----  end of class ConcreteFlyweight  ----- */



#endif 
