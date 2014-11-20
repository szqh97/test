#include "Decrator.h"
#include <iostream>
using namespace std;
Component::Component() {}

Component::~Component(){}

SalesTicket::SalesTicket(){}

SalesTicket::~SalesTicket(){}

void SalesTicket::prtTicket()
{
    cout << "SalesTicket::prtTickets" << endl;
}

TicketDecrator::TicketDecrator(Component* c)
{
    myTrailer = c;
}

TicketDecrator::~TicketDecrator()
{
    delete myTrailer;
    myTrailer = 0;
}

void TicketDecrator::callTrailer()
{
    cout << "TicketDecrator::callTrailer()" << endl;
    if (myTrailer)
        myTrailer->prtTicket();
}

Header1::Header1(Component* c):TicketDecrator(c){}

Header1::~Header1(){}

void Header1::prtTicket()
{
    cout << "Header1::prtTicket" << endl;
    callTrailer();
}

Header2::Header2(Component* c):TicketDecrator(c){}

Header2::~Header2(){}

void Header2::prtTicket()
{
    cout << "Header2::prtTicket" << endl;
    callTrailer();
}

Footer1::Footer1(Component* c):TicketDecrator(c){}

Footer1::~Footer1(){}

void Footer1::prtTicket()
{
    cout << "Footer1::prtTicket" << endl;
    callTrailer();
}

Footer2::Footer2(Component* c):TicketDecrator(c){}

Footer2::~Footer2(){}

void Footer2::prtTicket()
{
    cout << "Footer2::prtTicket" << endl;
    callTrailer();
}
