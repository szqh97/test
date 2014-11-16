
#ifndef  V1Drawing_INC
#define  V1Drawing_INC
#include "Drawing.h"


/*
 * =====================================================================
 *        Class:  V1Drawing
 *  Description:  
 * =====================================================================
 */
class V1Drawing : public Drawing
{
    public:
        V1Drawing ();                             /* constructor      */
        ~V1Drawing ();                            /* destructor       */
        void drawLine(double, double, double, double);
        void drawCircle(double, double, double);
    protected:
    private:
}; /* -----  end of class V1Drawing  ----- */

#endif   /* ----- #ifndef V1Drawing_INC  ----- */
