
#ifndef  _LRPD_H_
#define  _LRPD_H_
#include "PrintDriver.h"

class LRPD : public PrintDriver
{
    public:
        LRPD ();                             /* constructor      */
        ~LRPD ();                            /* destructor       */
        virtual void print();

    protected:
    private:

}; /* -----  end of class LRPD  ----- */

#endif   /* ----- #ifndef _LRPD_H_  ----- */
