#ifndef  _Template_H_
#define  _Template_H_

class AbstractClass
{
    public:
        AbstractClass ();                             /* constructor      */
        ~AbstractClass ();                            /* destructor       */
        void TemplateMethod();
        virtual void Primitive1() = 0;
        virtual void Primitive2() = 0;
    protected:
    private:
}; /* -----  end of class AbstractClass  ----- */

class ConcreteClass1 : public AbstractClass
{
    public:
        ConcreteClass1 ();                             /* constructor      */
        ~ConcreteClass1 ();                            /* destructor       */
        void Primitive1();
        void Primitive2();

    protected:

    private:

}; /* -----  end of class ConcreteClass1  ----- */


class ConcreteClass2 : public AbstractClass
{
    public:
        ConcreteClass2 ();                             /* constructor      */
        ~ConcreteClass2 ();                            /* destructor       */
        void Primitive1();
        void Primitive2();

    protected:

    private:

}; /* -----  end of class ConcreteClass2  ----- */



#endif   /* ----- #ifndef _Template_H_  ----- */
