#ifndef  Drawing_INC
#define  Drawing_INC

/*
 * =====================================================================
 *        Class:  Drawing
 *  Description:  
 * =====================================================================
 */
class Drawing
{
    public:
        Drawing (){};                             /* constructor      */
        ~Drawing (){};                            /* destructor       */
        void virtual drawLine(double, double, double, double) = 0;
        void virtual drawCircle(double, double, double) = 0;
    protected:
    private:
}; /* -----  end of class Drawing  ----- */

#endif   /* ----- #ifndef Drawing_INC  ----- */
