#include "Observer.h"
Customer::Customer(){}

Customer::~Customer(){}

void Customer::attach(Observer* myobserver)
{
    
    myobs.push_back(myobserver);
}

void Customer::deattach(Observer* myobserver)
{
    for (int i = 0; i <myobs.size(); ++i)
    {
        if (myobs[i] == myobserver)
        {
            myobs.erase(myobs.begin() + i);
            return;
        }
    }
}

void Customer::notify()
{
    for (vector<Observer*>::iterator iter = myobs.begin(); iter != myobs.end(); ++iter)
    {
        (*iter)->update();
        //(*iter)->update(this);
    }
}

Observer::Observer(){}

Observer::~Observer(){}

WelcomeLetter::WelcomeLetter(){}

WelcomeLetter::~WelcomeLetter(){}

void WelcomeLetter::update()
//void WelcomeLetter::update(Customer* c)
{
    cout << "upate in WelcomeLetter" << endl;
}

AddrVerification::AddrVerification(){}

AddrVerification::~AddrVerification(){}

void AddrVerification::update()
//void AddrVerification::update(Customer* c)
{
    cout << "update in AddrVerification" << endl;
}
