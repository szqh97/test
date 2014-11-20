
#ifndef  _Abstraction_H_
#define  _Abstraction_H_

class AbstractionImpl;

class Abstraction
{
    public:
        virtual ~Abstraction ();                            /* destructor       */
        virtual void Operation() = 0;

    protected:
        Abstraction();
    private:

}; /* -----  end of class Abstracion  ----- */


class RefinedAbstraction : public Abstraction
{
    public:
        RefinedAbstraction (AbstractionImpl* impl);                             /* constructor      */
        ~RefinedAbstraction ();                            /* destructor       */
        void Operation();
    protected:

    private:
        AbstractionImpl* _impl;

}; /* -----  end of class RefinedAbstraction  ----- */

#endif   /* ----- #ifndef _Abstraction_H_  ----- */
