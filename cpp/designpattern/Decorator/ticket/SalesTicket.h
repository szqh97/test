
#ifndef  _SalesTicket_H_
#define  _SalesTicket_H_
#include "Component.h"

class SalesTicket : public Component
{
    public:
        SalesTicket ();                             /* constructor      */
        ~SalesTicket ();                            /* destructor       */
        void prtTicket();

    protected:
    private:
}; /* -----  end of class SalesTicket  ----- */

#endif   /* ----- #ifndef _SalesTicket_H_  ----- */
