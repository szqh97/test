
#ifndef  Rectangle_INC
#define  Rectangle_INC
#include "Shape.h"

/*
 * =====================================================================
 *        Class:  Rectangle
 *  Description:  
 * =====================================================================
 */
class Rectangle : public Shape
{
    public:
        Rectangle (Drawing*, double, double, double, double);                             /* constructor      */
        ~Rectangle ();                            /* destructor       */
        //virtual void drawLine(double, double, double, double) = 0;
        void draw();
    protected:
    private:
        double _x1, _y1, _x2, _y2;
}; /* -----  end of class Rectangle  ----- */

#endif   /* ----- #ifndef Rectangle_INC  ----- */
