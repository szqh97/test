#include "Footer1.h"
#include <iostream>
using namespace std;
Footer1::Footer1(Component* myComponent):TicketDecorator(myComponent)
{
}

Footer1::~Footer1(){}

void Footer1::prtTicket()
{
    cout << "Footer1" << endl;
    this->callTrailer();
}


