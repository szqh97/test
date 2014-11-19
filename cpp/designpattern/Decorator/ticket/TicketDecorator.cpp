#include "TicketDecorator.h"
#include <iostream>
using namespace std;
TicketDecorator::TicketDecorator(Component* myComponent)
{
    myTrailer = myComponent;
}

TicketDecorator::~TicketDecorator(){}

void TicketDecorator::callTrailer()
{
    cout << "TicketDecorator::callTrailer()" << endl;
    if (myTrailer)
    {
        myTrailer->prtTicket();
    }
}

