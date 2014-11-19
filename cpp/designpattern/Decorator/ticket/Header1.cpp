#include "Header1.h"
#include <iostream>
using namespace std;
Header1::Header1(Component* myComponent):TicketDecorator(myComponent)
{
}

Header1::~Header1(){}

void Header1::prtTicket()
{
    cout << "Header1" << endl;
    this->callTrailer();
}

