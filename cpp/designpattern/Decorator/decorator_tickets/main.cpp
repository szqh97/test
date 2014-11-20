#include "Decrator.h"
#include <iostream>
using namespace std;

class Factory
{
    public:
        Factory ();  
        ~Factory ();
        Component* getComponent();

    protected:
    private:

};

Factory::Factory(){}

Factory::~Factory(){}

Component* Factory::getComponent()
{ 

    SalesTicket* ticket = new SalesTicket();
    TicketDecrator* pdec = new Footer1(ticket);
    pdec = new Footer2(pdec);
    pdec = new Header1(pdec);
    pdec = new Header2(pdec);

    return pdec;
}


int main ( int argc, char *argv[] )
{
    Factory fact = Factory();
    Component* cp = fact.getComponent();
    cp->prtTicket();
    delete cp;

    return 0;
}			/* ----------  end of function main  ---------- */
