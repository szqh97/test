#include "Factory.h"
Factory::Factory(){}
Factory::~Factory(){}

Component* Factory::getComponent()
{
    bool doHeader1, doHeader2, doFooter1, doFooter2;
    doHeader1 = true;
    doHeader2 = false;
    doFooter1 = true;
    doFooter2 = false;

    Component* myComponent;
    myComponent = new SalesTicket;
    if (doHeader1) myComponent = new Footer2(myComponent);
    return myComponent;
}

