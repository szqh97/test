#ifndef  _Proxy_H_
#define  _Proxy_H_

class Subject
{
public:
    virtual ~Subject ();    
    virtual void Request() = 0;

protected:
    Subject ();     
};

class ConcreteSubject: public Subject
{
public:
    ConcreteSubject ();         
    ~ConcreteSubject ();        
    void Request();

}; 


class Proxy
{
    public:
        Proxy () = default;        
        Proxy(Subject* sub);
        ~Proxy ();        
        void Request();
    private:
        Subject* _sub;

}; 



#endif  
