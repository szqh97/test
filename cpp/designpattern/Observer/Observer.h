#ifndef  _Observer_H_
#define  _Observer_H_
#include "Subject.h"
class Observer
{
    public:
        Observer ();        
        virtual ~Observer ();      
        virtual void update(Subject*) = 0;
        virtual void printInfo() = 0;
    protected:
        State _st;
    private:
}; 

class ConcreteObserverA : Observer
{
    public:
        ConcreteObserverA (Subject*);    
        virtual ~ConcreteObserverA ();  
        virtual Subject* getSubject();
        void update(Subject*);
        void printInfo();
    protected:
    private:
        Subject* _sub;

}; /* -----  end of class ConcreteObserverA  ----- */

class ConcreteObserverB : Observer
{
    public:
        ConcreteObserverB (Subject*);    
        virtual ~ConcreteObserverB ();  
        virtual Subject* getSubject();
        void update(Subject*);
        void printInfo();
    protected:
    private:
        Subject* _sub;

}; /* -----  end of class ConcreteObserverB  ----- */



#endif 
