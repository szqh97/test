
#ifndef  _DisplayDriver_H_
#define  _DisplayDriver_H_

class DisplayDriver
{
    public:
        DisplayDriver ();                             /* constructor      */
        ~DisplayDriver ();                            /* destructor       */
        virtual void draw() = 0;


    protected:

    private:

}; /* -----  end of class DisplayDriver  ----- */

#endif   /* ----- #ifndef _DisplayDriver_H_  ----- */
