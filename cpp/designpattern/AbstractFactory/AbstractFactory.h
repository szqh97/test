
#ifndef  _AbstractFactory_H_
#define  _AbstractFactory_H_
#include "Product.h"
class AbstractProductA;
class AbstractProductB;

class AbstracFactory
{
    public:
        AbstracFactory ();                             /* constructor      */
        virtual ~AbstracFactory ();                            /* destructor       */
        virtual AbstractProductA* createProductA() = 0;
        virtual AbstractProductB* createProductB() = 0;
    protected:
    private:
}; /* -----  end of class AbstracFactory  ----- */


class ConcreteFactory1 : public AbstracFactory
{
    public:
        ConcreteFactory1 ();                             /* constructor      */
        ~ConcreteFactory1 ();                            /* destructor       */
        AbstractProductA* createProductA();
        AbstractProductB* createProductB();
    protected:
    private:

}; /* -----  end of class ConcreteFactory1  ----- */

class ConcreteFactory2 : public AbstracFactory
{
    public:
        ConcreteFactory2 ();                             /* constructor      */
        ~ConcreteFactory2 ();                            /* destructor       */
        AbstractProductA* createProductA();
        AbstractProductB* createProductB();
    protected:
    private:
}; /* -----  end of class ConcreteFactory2  ----- */


#endif   /* ----- #ifndef _AbstractFactory_H_  ----- */
