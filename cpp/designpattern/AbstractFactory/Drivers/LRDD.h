
#ifndef  _LRDD_H_
#define  _LRDD_H_
#include "DisplayDriver.h"

class LRDD: public DisplayDriver
{
    public:
        LRDD();                             /* constructor      */
        ~LRDD();                            /* destructor       */
        virtual void draw();
    protected:
    private:
}; /* -----  end of class LRDD----- */

#endif   /* ----- #ifndef _LRDD_H_  ----- */
