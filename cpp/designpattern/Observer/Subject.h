#ifndef  _Subject_H_
#define  _Subject_H_
#include <list>
#include <string>
using namespace std;
typedef string State;

class Observer;

class Subject
{
    public:
        Subject ();        
        virtual ~Subject ();     
        virtual void attach(Observer*);
        virtual void detach(Observer*);
        virtual void notify();
        virtual void setState(const State&) = 0;
        virtual State getState() = 0;
    protected:
    private:
        list<Observer*>* _obvs;

}; 

class ConcreteSubject : public Subject
{
    public:
        ConcreteSubject ();          
        ~ConcreteSubject ();    
        State getState();
        void setState(const State&);
    protected:
        State _st;
    private:
}; 




#endif  
