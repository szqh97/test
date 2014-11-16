
#ifndef  Rectangle_INC
#define  Rectangle_INC
#include "Shape.h"

/*
 * =====================================================================
 *        Class:  Rectangle
 *  Description:  
 * =====================================================================
 */
class Rectangle
{
    public:
        Rectangle ();                             /* constructor      */
        Rectangle ( const Rectangle &other );   /* copy constructor */
        ~Rectangle ();                            /* destructor       */
        Rectangle& operator = ( const Rectangle &other ); /* assignment operator */
    protected:
    private:
}; /* -----  end of class Rectangle  ----- */

#endif   /* ----- #ifndef Rectangle_INC  ----- */
