
#ifndef  Factory_INC
#define  Factory_INC
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Drawing.h"
#include "V2Drawing.h"
#include "V1Drawing.h"

/*
 * =====================================================================
 *        Class:  Factory
 *  Description:  
 * =====================================================================
 */
class Factory
{
    public:
        Factory ();                             /* constructor      */
        ~Factory ();                            /* destructor       */
        Shape** getShape();
    protected:
    private:
}; /* -----  end of class Factory  ----- */

#endif   /* ----- #ifndef Factory_INC  ----- */
