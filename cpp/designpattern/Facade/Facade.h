//Facade.h
#ifndef _FACADE_H_
#define _FACADE_H_

/*
 * =======================================================================
 *        Class:  Subsystem1
 *  Description:  
 * =======================================================================
 */
class Subsystem1
{
    public:
        /* =================  LIFECYCLE     =================== */
        Subsystem1 ();                   /* constructor */
        ~Subsystem1();
        void Operation();

    protected:
    private:

}; /* -----  end of class Subsystem1  ----- */


/*
 * =======================================================================
 *        Class:  Subsystem2
 *  Description:  
 * =======================================================================
 */
class Subsystem2
{
    public:
        /* =================  LIFECYCLE     =================== */
        Subsystem2 ();                   /* constructor */
        ~Subsystem2();

        void Operation();

    protected:
        /* ====================  METHODS       ================ */

        /* ====================  DATA MEMBERS  ================ */

    private:
        /* ====================  METHODS       ================ */

        /* ====================  DATA MEMBERS  ================ */

}; /* -----  end of class Subsystem2  ----- */

/*
 * =======================================================================
 *        Class:  Facade
 *  Description:  
 * =======================================================================
 */
class Facade
{
    public:
        /* =================  LIFECYCLE     =================== */
        Facade ();                   /* constructor */
        ~Facade();

        /* ====================  ACCESSORS     ================ */

        /* ====================  MUTATORS      ================ */

        /* ====================  OPERATORS     ================ */
        void OperationWrapper();

    protected:
        /* ====================  METHODS       ================ */

        /* ====================  DATA MEMBERS  ================ */

    private:
        /* ====================  METHODS       ================ */

        /* ====================  DATA MEMBERS  ================ */
        Subsystem1* _subs1;
        Subsystem2* _subs2;

}; /* -----  end of class Facade  ----- */

#endif

