
#ifndef  _Abstraction_H_
#define  _Abstraction_H_

class AbstractionImpl;

class Abstraction
{
    public:
        virtual ~Abstraction ();    
        virtual void Operation() = 0;

    protected:
        Abstraction();
    private:

};


class RefinedAbstraction : public Abstraction
{
    public:
        RefinedAbstraction (AbstractionImpl* impl);   
        ~RefinedAbstraction ();                      
        void Operation();
    protected:

    private:
        AbstractionImpl* _impl;

}; 

#endif  
