#ifndef  Strategy_INC
#define  Strategy_INC
class Strategy;

/*
 * =====================================================================
 *        Class:  Context
 *  Description:  
 * =====================================================================
 */
class Context
{
    public:
        Context (Strategy* pStrategy);                             /* constructor      */
        ~Context ();                            /* destructor       */
        void ContextInterface();
    protected:

    private:
        Strategy* m_pStrategy;
}; /* -----  end of class Context  ----- */

/*
 * =====================================================================
 *        Class:  Strategy
 *  Description:  
 * =====================================================================
 */
class Strategy
{
    public:
        Strategy ();                             /* constructor      */
        virtual ~Strategy () ;                            /* destructor       */
        void virtual AlgorithmInterface()=0;
    protected:
    private:
}; /* -----  end of class Strategy  ----- */

/*
 * =======================================================================
 *        Class:  ConcreateStrageA
 *  Description:  
 * =======================================================================
 */
class ConcreateStrageA : public Strategy
{
    public:
        ConcreateStrageA () ;                  /* constructor */
        virtual ~ConcreateStrageA();
        virtual void AlgorithmInterface();

    protected:

    private:

}; /* -----  end of class ConcreateStrageA  ----- */

#endif   /* ----- #ifndef Strategy_INC  ----- */
