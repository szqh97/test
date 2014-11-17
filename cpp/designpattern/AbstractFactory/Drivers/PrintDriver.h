
#ifndef  _PrintDriver_H_
#define  _PrintDriver_H_

class PrintDriver
{
    public:
        PrintDriver ();                             /* constructor      */
        ~PrintDriver ();                            /* destructor       */
        virtual void print() = 0;
    protected:
    private:

}; /* -----  end of class PrintDriver  ----- */

#endif   /* ----- #ifndef _PrintDriver_H_  ----- */
