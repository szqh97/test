
#ifndef  _AppControl_H_
#define  _AppControl_H_
#include "DisplayDriver.h"
#include "PrintDriver.h"
#include "ResFactory.h"

class AppControl
{
    public:
        AppControl (int );                             /* constructor      */
        ~AppControl ();                            /* destructor       */
        void doPrint();
        void doDraw();

    protected:

    private:
        ResFactory *myResFactory;
        DisplayDriver *myDisplayDriver;
        PrintDriver *myPrintDriver;

}; /* -----  end of class AppControl  ----- */

#endif   /* ----- #ifndef _AppControl_H_  ----- */
