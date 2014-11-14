#ifndef  USTax_INC
#define  USTax_INC
#include "CalcTax.h"
/*
 * =====================================================================
 *        Class:  USTax
 *  Description:  
 * =====================================================================
 */
class USTax : virtual public CalcTax
{
    public:
        USTax ();                             /* constructor      */
        ~USTax ();                            /* destructor       */
        double taxAmount(long, double);
    protected:
    private:
}; /* -----  end of class USTax  ----- */

#endif   /* ----- #ifndef USTax_INC  ----- */
