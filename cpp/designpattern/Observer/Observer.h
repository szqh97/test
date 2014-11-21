#ifndef  _Observer_H_
#define  _Observer_H_
#include "Subject.h"
#include <string>
typedef string State;
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

class ConcreteObserverA : public Observer
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

}; 

class ConcreteObserverB : public Observer
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

};



#endif 
