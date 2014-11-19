#ifndef  _Header2_H_
#define  _Header2_H_
#include "TicketDecorator.h"

class Header2 : public TicketDecorator
{
    public:
        Header2 (Component*);                             /* constructor      */
        ~Header2 ();                            /* destructor       */
        void prtTicket();

    protected:

    private:

}; /* -----  end of class Header2  ----- */


#endif   /* ----- #ifndef _Header2_H_  ----- */
