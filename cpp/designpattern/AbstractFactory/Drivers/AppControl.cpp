#include "AppControl.h"
AppControl::AppControl(int type)
{
    myResFactory = ResFactory::getFactory(type);
    myDisplayDriver = myResFactory->getDispDrv();
    myPrintDriver = myResFactory->getPrntDrv();
}

AppControl::~AppControl()
{
    delete myDisplayDriver;
    myDisplayDriver = 0;
    delete myPrintDriver;
    myPrintDriver = 0;
    delete myResFactory;
    myResFactory = 0;
}

void AppControl::doDraw()
{
    myDisplayDriver->draw();
}

void AppControl::doPrint()
{
    myPrintDriver->print();
}

