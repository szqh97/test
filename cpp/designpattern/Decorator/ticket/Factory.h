
#ifndef  _Factory_H_
#define  _Factory_H_
#include "Component.h"
#include "SalesTicket.h"
#include "Header1.h"
#include "Header2.h"
#include "Footer1.h"
#include "Footer2.h"

class Factory
{
    public:
        Factory ();                             /* constructor      */
        ~Factory ();                            /* destructor       */
        Component* getComponent();
    protected:
    private:

}; /* -----  end of class Factory  ----- */


#endif   /* ----- #ifndef _Factory_H_  ----- */
