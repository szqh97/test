
#ifndef  _HRDD_H_
#define  _HRDD_H_
#include "DisplayDriver.h"

class HRDD : public DisplayDriver
{
    public:
        HRDD ();                             /* constructor      */
        ~HRDD ();                            /* destructor       */
        virtual void draw();
    protected:
    private:

}; /* -----  end of class HRDD  ----- */

#endif   /* ----- #ifndef _HRDD_H_  ----- */
