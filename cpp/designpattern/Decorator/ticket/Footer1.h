#ifndef  _Footer1_H_
#define  _Footer1_H_
#include "TicketDecorator.h"

class Footer1 : public TicketDecorator
{
    public:
        Footer1 (Component*);                             /* constructor      */
        ~Footer1 ();                            /* destructor       */
        void prtTicket();

    protected:

    private:

}; /* -----  end of class Footer1  ----- */


#endif   /* ----- #ifndef _Footer1_H_  ----- */
