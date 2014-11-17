
#ifndef  _ResFactory_H_
#define  _ResFactory_H_
#include "DisplayDriver.h"
#include "PrintDriver.h"

class ResFactory
{
    public:
        ResFactory ();                             /* constructor      */
        ~ResFactory ();                            /* destructor       */
        virtual DisplayDriver* getDispDrv() = 0;
        virtual PrintDriver* getPrntDrv() = 0;
        static ResFactory* getFactory(int type);
}; /* -----  end of class ResFactory  ----- */

#endif   /* ----- #ifndef _ResFactory_H_  ----- */
