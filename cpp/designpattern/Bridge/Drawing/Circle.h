
#ifndef  Circle_INC
#define  Circle_INC
#include "Shape.h"
/*
 * =====================================================================
 *        Class:  Circle
 *  Description:  
 * =====================================================================
 */
class Circle : public Shape
{
    public:
        Circle (Drawing*, double, double, double);                             /* constructor      */
        ~Circle ();                            /* destructor       */
    protected:
        virtual void draw();
        virtual void drawCircle(double, double, double) = 0;
    private:
        double _x, _y, _r;
}; /* -----  end of class Circle  ----- */

#endif   /* ----- #ifndef Circle_INC  ----- */
