#include "Factory.h"
Factory::Factory(){}
Factory::~Factory(){}

Component* Factory::getComponent()
{
    SalesTicket* mySalesTicket = new SalesTicket();
    TicketDecorator* myComponent = 0;

    myComponent = new Header1( mySalesTicket);
    myComponent = new Footer2( myComponent );
    myComponent = new Footer1( myComponent );
    myComponent = new Header2( myComponent );
    myComponent->callTrailer();


    delete myComponent;
    //delete mySalesTicket;


    return myComponent;
}

