#include "Footer2.h"
#include <iostream>
using namespace std;
Footer2::Footer2(Component* myComponent):TicketDecorator(myComponent)
{
}

Footer2::~Footer2(){}

void Footer2::prtTicket()
{
    cout << "Footer2" << endl;
    this->callTrailer();
}



