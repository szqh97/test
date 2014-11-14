
#ifndef  SalesOrder_INC
#define  SalesOrder_INC
#include "CalcTax.h"

/*
 * =====================================================================
 *        Class:  SalesOrder
 *  Description:  
 * =====================================================================
 */
class SalesOrder
{
    public:
        SalesOrder ();                             /* constructor      */
        ~SalesOrder ();                            /* destructor       */
        void process(CalcTax* TaxToUse);
    protected:
    private:
}; /* -----  end of class SalesOrder  ----- */

#endif   /* ----- #ifndef SalesOrder_INC  ----- */
