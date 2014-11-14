#ifndef  CalcTax_INC
#define  CalcTax_INC

/*
 * =====================================================================
 *        Class:  CalcTax
 *  Description:  
 * =====================================================================
 */
class CalcTax
{
    public:
        CalcTax ();                             /* constructor      */
        ~CalcTax ();                            /* destructor       */
        double virtual taxAmount(long, double)=0;

    protected:
    private:

}; /* -----  end of class CalcTax  ----- */

#endif   /* ----- #ifndef CalcTax_INC  ----- */
