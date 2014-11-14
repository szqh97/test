
#ifndef  adapter_INC
#define  adapter_INC

/*
 * =======================================================================
 *        Class:  Target
 *  Description:  
 * =======================================================================
 */
class Target
{
    public:
        Target ();                   /* constructor */
        virtual ~Target();
        virtual void Request();
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
class Adapter : public Target
{
    public:
        Adapter (Adaptee* ade);                             /* constructor      */
        ~Adapter ();                            /* destructor       */
        void Request();

    protected:
    private:
        Adaptee* _ade;
}; /* -----  end of class Adapter  ----- */

#endif   /* ----- #ifndef adapter_INC  ----- */
