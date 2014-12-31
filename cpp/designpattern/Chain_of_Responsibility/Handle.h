#ifndef  _Handle_H_
#define  _Handle_H_

class Handle
{
public:
    virtual ~Handle ();  
    virtual void HandleRequest() = 0;
    void setSuccessor(Handle*);
    Handle* getSuccessor();

protected:
    Handle () = default;    
    Handle(Handle* );
private:
    Handle* _succ;
}; 


class ConcreteHandleA:public Handle
{
public:
    ConcreteHandleA () = default;     
    ConcreteHandleA(Handle* succ);
    void HandleRequest();
    ~ConcreteHandleA ();   
};

class ConcreteHandleB:public Handle
{
public:
    ConcreteHandleB () = default;     
    ConcreteHandleB(Handle* succ);
    void HandleRequest();
    ~ConcreteHandleB ();   

};

#endif   
