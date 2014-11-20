#ifndef  _TicketDecorator_H_
#define  _TicketDecorator_H_
#include "Component.h"

class TicketDecorator : public Component
{
    public:
        TicketDecorator (Component* );                   /* constructor */
        virtual ~TicketDecorator();
        void callTrailer();

    protected:
    private:
        Component* myTrailer;

}; /* -----  end of class TicketDecorator  ----- */


#endif   /* ----- #ifndef _TicketDecorator_H_  ----- */
