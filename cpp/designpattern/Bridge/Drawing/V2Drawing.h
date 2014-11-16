
#ifndef  V2Drawing_INC
#define  V2Drawing_INC
#include "Drawing.h"


/*
 * =====================================================================
 *        Class:  V2Drawing
 *  Description:  
 * =====================================================================
 */
class V2Drawing
{
    public:
        V2Drawing ();                             /* constructor      */
        ~V2Drawing ();                            /* destructor       */
        void drawLine(double, double, double, double);
        void drawCircle(double, double, double);
    protected:
    private:
}; /* -----  end of class V2Drawing  ----- */

#endif   /* ----- #ifndef V2Drawing_INC  ----- */
