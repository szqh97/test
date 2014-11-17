
#ifndef  _Product_H_
#define  _Product_H_

class AbstractProductA
{
    public:
        AbstractProductA ();                             /* constructor      */
        virtual ~AbstractProductA ();                            /* destructor       */
        virtual void Operation() = 0;
    protected:
    private:

}; /* -----  end of class AbstractProductA  ----- */


class AbstractProductB
{
    public:
        AbstractProductB ();                             /* constructor      */
        virtual ~AbstractProductB ();                            /* destructor       */
        virtual void Operation() = 0;

    protected:

    private:

}; /* -----  end of class AbstractProductB  ----- */

class ProductA1 : public AbstractProductA
{
    public:
        ProductA1 ();                             /* constructor      */
        ~ProductA1 ();                            /* destructor       */
        void Operation();
    protected:
    private:

}; /* -----  end of class ProductA1  ----- */

class ProductA2 : public AbstractProductA
{
    public:
        ProductA2 ();                             /* constructor      */
        ~ProductA2 ();                            /* destructor       */
        void Operation();

    protected:
    private:
}; /* -----  end of class ProductA2  ----- */

class ProductB1 : public AbstractProductB
{
    public:
        ProductB1 ();                             /* constructor      */
        ~ProductB1 ();                            /* destructor       */
        void Operation();
    protected:
    private:
}; /* -----  end of class ProductB1  ----- */

class ProductB2 : public AbstractProductB
{
    public:
        ProductB2 ();                             /* constructor      */
        ~ProductB2 ();                            /* destructor       */
        void Operation();
    protected:
    private:
}; /* -----  end of class ProductB2  ----- */

#endif   /* ----- #ifndef _Product_H_  ----- */
