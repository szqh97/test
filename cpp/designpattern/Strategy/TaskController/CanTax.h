#ifndef  CanTax_INC
#define  CanTax_INC
#include "CalcTax.h"
/*
 * =====================================================================
 *        Class:  CanTax
 *  Description:  
 * =====================================================================
 */
class CanTax : virtual public CalcTax
{
    public:
        CanTax ();                             /* constructor      */
        ~CanTax ();                            /* destructor       */
        double taxAmount(long, double);
    protected:
    private:
}; /* -----  end of class CanTax  ----- */

#endif   /* ----- #ifndef CanTax_INC  ----- */
