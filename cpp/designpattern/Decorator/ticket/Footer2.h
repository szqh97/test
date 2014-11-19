#ifndef  _Footer2_H_
#define  _Footer2_H_
#include "TicketDecorator.h"

class Footer2 : public TicketDecorator
{
    public:
        Footer2 (Component*);                             /* constructor      */
        ~Footer2 ();                            /* destructor       */
        void prtTicket();

    protected:
    private:

}; /* -----  end of class Footer2  ----- */


#endif   /* ----- #ifndef _Footer2_H_  ----- */
