#ifndef  _Header1_H_
#define  _Header1_H_
#include "TicketDecorator.h"

class Header1 : public TicketDecorator
{
    public:
        Header1 (Component*);                             /* constructor      */
        ~Header1 ();                            /* destructor       */
        void prtTicket();

    protected:

    private:

}; /* -----  end of class Header1  ----- */


#endif   /* ----- #ifndef _Header1_H_  ----- */
