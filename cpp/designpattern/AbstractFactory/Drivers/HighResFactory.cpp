#include "HighResFactory.h"

HighResFactory::HighResFactory(){}

HighResFactory::~HighResFactory(){}

DisplayDriver* HighResFactory::getDispDrv()
{
    return new HRDD;
}

PrintDriver* HighResFactory::getPrntDrv()
{
    return new HRPD;
}


