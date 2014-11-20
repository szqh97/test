#ifndef  _Observer_H_
#define  _Observer_H_
#include <iostream>
#include <vector>

using namespace std;

class Observer;
class Customer
{
    public:
        Customer ();     
        ~Customer ();   
        void attach(Observer*);
        void deattach(Observer*);
        void notify();
    protected:
    private:
        vector<Observer*> myobs;

}; /* -----  end of class Customer  ----- */

class Observer
{
    public:
        Observer ();      
        virtual ~Observer ();  
        virtual void update() = 0;
        //virtual void update(Customer*) = 0;
    protected:
    private:

}; 


class WelcomeLetter : public Observer
{
    public:
        WelcomeLetter ();           
        ~WelcomeLetter();
        void update();
        //void update(Customer*);
    protected:
    private:

}; 


class AddrVerification : public Observer
{
    public:
        AddrVerification (); 
        ~AddrVerification (); 
        void update();
        //void update(Customer*);
    protected:
    private:

}; 




#endif   /* ----- #ifndef _Observer_H_  ----- */
