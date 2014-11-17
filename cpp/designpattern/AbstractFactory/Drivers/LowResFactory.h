
#ifndef  _LowResFactory_H_
#define  _LowResFactory_H_
#include "ResFactory.h"
#include "DisplayDriver.h"
#include "PrintDriver.h"
#include "LRDD.h"
#include "LRPD.h"
class LowResFactory : public ResFactory
{
    public:
        LowResFactory ();                             /* constructor      */
        ~LowResFactory ();                            /* destructor       */
        DisplayDriver* getDispDrv();
        PrintDriver* getPrntDrv();
}; /* -----  end of class LowResFactory  ----- */

#endif   /* ----- #ifndef _LowResFactory_H_  ----- */
