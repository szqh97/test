#ifndef _SHAPE_H_
#define _SHAPE_H_
/*
 * =====================================================================
 *        Class:  Shape
 *  Description:  
 * =====================================================================
 */
class Shape
{
    public:
        Shape ();                             /* constructor      */
        ~Shape ();                            /* destructor       */
        void virtual display() = 0; 
    protected:

    private:

}; /* -----  end of class Shape  ----- */

#endif
