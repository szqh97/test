#include "ResFactory.h"
#include "HighResFactory.h"
#include "LowResFactory.h"
ResFactory::ResFactory(){}

ResFactory::~ResFactory(){}

ResFactory* ResFactory::getFactory(int type)
{
   if (0 == type)
   {
       return new HighResFactory;
   }
   else {
       return new LowResFactory;
   }
}

