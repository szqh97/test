#ifndef  Shape_INC
#define  Shape_INC
#include "Drawing.h"

/*
 * =====================================================================
 *        Class:  Shape
 *  Description:  
 * =====================================================================
 */
class Shape
{
    public:
        Shape (Drawing *aDrawing) ;                             /* constructor      */
        void virtual draw() = 0;
        ~Shape ();                            /* destructor       */
    protected:
        Drawing* myDrawing;
        void drawLine(double, double, double, double);
        void drawCircle(double, double, double) ;
    private:
}; /* -----  end of class Shape  ----- */


#endif   /* ----- #ifndef Shape_INC  ----- */
