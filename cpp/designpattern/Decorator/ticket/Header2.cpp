#include "Header2.h"
#include <iostream>
using namespace std;
Header2::Header2(Component* myComponent):TicketDecorator(myComponent)
{
}

Header2::~Header2(){}

void Header2::prtTicket()
{
    cout << "Header2" << endl;
    this->callTrailer();
}


