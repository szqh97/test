
#ifndef  TaskController_INC
#define  TaskController_INC
#include "CalcTax.h"

/*
 * =====================================================================
 *        Class:  TaskController
 *  Description:  
 * =====================================================================
 */
class TaskController
{
    public:
        TaskController ();                             /* constructor      */
        ~TaskController ();                            /* destructor       */
        void process(int);
        CalcTax* getTaxRules4Country(int);
        void releaseCalcTax(CalcTax*);
    protected:
    private:
}; /* -----  end of class TaskController  ----- */


#endif   /* ----- #ifndef TaskController_INC  ----- */
