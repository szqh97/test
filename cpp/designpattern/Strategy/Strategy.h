#ifndef  Strategy_INC
#define  Strategy_INC
class Strategy;

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

class Strategy
{
    public:
        Strategy ();                             /* constructor      */
        virtual ~Strategy () ;                            /* destructor       */
        void virtual AlgorithmInterface()=0;
    protected:
    private:
}; /* -----  end of class Strategy  ----- */

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
