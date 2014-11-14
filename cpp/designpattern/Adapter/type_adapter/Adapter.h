// Adapter.h

#ifndef  Adapter_INC
#define  Adapter_INC

/*
 * =====================================================================
 *        Class:  Target
 *  Description:  
 * =====================================================================
 */
class Target
{
    public:
        Target ();                             /* constructor      */
        virtual ~Target ();                            /* destructor       */
        void virtual Request();
    protected:
    private:
}; /* -----  end of class Target  ----- */

/*
 * =====================================================================
 *        Class:  Adaptee
 *  Description:  
 * =====================================================================
 */
class Adaptee
{
    public:
        Adaptee ();                             /* constructor      */
        ~Adaptee ();                            /* destructor       */
        void SpecificRequest();
    protected:
    private:

}; /* -----  end of class Adaptee  ----- */


/*
 * =====================================================================
 *        Class:  Adapter
 *  Description:  
 * =====================================================================
 */
class Adapter : public Target, public Adaptee
{
    public:
        Adapter ();                             /* constructor      */
        ~Adapter ();                            /* destructor       */
        void Request();
    protected:
    private:
}; /* -----  end of class Adapter  ----- */

#endif   /* ----- #ifndef Adapter_INC  ----- */
