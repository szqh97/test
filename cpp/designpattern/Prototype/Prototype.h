
#ifndef  _Prototype_H_
#define  _Prototype_H_


class Prototype
{
    public:
        virtual ~Prototype();
        virtual Prototype* Clone() const = 0;

    protected:
        Prototype();

    private:

}; 



class ConcretePrototype: public Prototype
{
    public:
        ConcretePrototype() = default; 
        ConcretePrototype (const ConcretePrototype& cp);
        ~ConcretePrototype();
        Prototype* Clone() const;

    protected:

    private:

}; /* -----  end of class ConcretePrototype  ----- */

#endif 
