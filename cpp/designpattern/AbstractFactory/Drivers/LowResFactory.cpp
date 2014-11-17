#include "LowResFactory.h"
LowResFactory::LowResFactory(){}

LowResFactory::~LowResFactory(){}

DisplayDriver* LowResFactory::getDispDrv()
{
    return new LRDD;
}

PrintDriver* LowResFactory::getPrntDrv()
{
    return new LRPD;
}
