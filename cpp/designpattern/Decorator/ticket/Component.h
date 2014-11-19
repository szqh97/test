#ifndef  _component_H_
#define  _component_H_

class Component
{
    public:
        Component ();                             /* constructor      */
        ~Component ();                            /* destructor       */
        virtual void prtTicket() = 0;
    protected:
    private:
}; /* -----  end of class Component  ----- */


#endif   /* ----- #ifndef _component_H_  ----- */
