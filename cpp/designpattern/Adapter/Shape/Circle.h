#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include "Shape.h"
#include "XX_Circle.h"
/*
 * =====================================================================
 *        Class:  Circle
 *  Description:  
 * =====================================================================
 */
class Circle : public Shape
{
    public:
        Circle (XX_Circle* xxcircle);                             /* constructor      */
        ~Circle ();                            /* destructor       */
        void display();
    protected:

    private:
        XX_Circle* myXX_Circle;

}; /* -----  end of class Circle  ----- */
#endif
