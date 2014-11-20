#include "TicketDecorator.h"
#include <iostream>
using namespace std;
TicketDecorator::TicketDecorator(Component* myComponent)
{
    myTrailer = myComponent;
}

TicketDecorator::~TicketDecorator()
{
    delete this->myTrailer;
    myTrailer = NULL;
}

void TicketDecorator::callTrailer()
{
    cout << "TicketDecorator::callTrailer()" << endl;
    if (myTrailer)
    {
        myTrailer->prtTicket();
    }
}

