
#ifndef  _HRPD_H_
#define  _HRPD_H_
#include "PrintDriver.h"

class HRPD : public PrintDriver
{
    public:
        HRPD ();                             /* constructor      */
        ~HRPD ();                            /* destructor       */
        virtual void print();
    protected:
    private:

}; /* -----  end of class HRPD  ----- */

#endif   /* ----- #ifndef _HRPD_H_  ----- */
