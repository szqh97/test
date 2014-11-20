
#ifndef  _AbstractionImp_H_
#define  _AbstractionImp_H_

class AbstractionImpl
{
    public:
        AbstractionImpl ();                             /* constructor      */
        virtual ~AbstractionImpl ();                            /* destructor       */
        virtual void Operation() = 0;

    protected:

    private:

}; /* -----  end of class AbstractionImpl  ----- */

class ConcreteAbstractionImplA : public AbstractionImpl
{
    public:
        ConcreteAbstractionImplA ();                             /* constructor      */
        ~ConcreteAbstractionImplA ();                            /* destructor       */
        virtual void Operation();

    protected:
    private:

}; /* -----  end of class ConcreteAbstractionImplA  ----- */

class ConcreteAbstractionImplB
{
    public:
        ConcreteAbstractionImplB ();                             /* constructor      */
        ~ConcreteAbstractionImplB ();                            /* destructor       */
        virtual void Operation();

    protected:
    private:

}; /* -----  end of class ConcreteAbstractionImplB  ----- */


#endif   /* ----- #ifndef _AbstractionImp_H_  ----- */


