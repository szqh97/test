
#ifndef  _HighResFactory_H_
#define  _HighResFactory_H_
#include "ResFactory.h"
#include "DisplayDriver.h"
#include "PrintDriver.h"
#include "HRDD.h"
#include "HRPD.h"

class HighResFactory : public ResFactory
{
    public:
        HighResFactory ();                             /* constructor      */
        ~HighResFactory ();                            /* destructor       */
        virtual DisplayDriver* getDispDrv();
        virtual PrintDriver* getPrntDrv();

    protected:
    private:

}; /* -----  end of class HighResFactory  ----- */

#endif   /* ----- #ifndef _HighResFactory_H_  ----- */
