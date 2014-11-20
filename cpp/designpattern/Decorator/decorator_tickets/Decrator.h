
#ifndef  Decrator_INC
#define  Decrator_INC

class Component
{
    public:
        Component ();     
        virtual ~Component ();      
        virtual void prtTicket() = 0;
    protected:
    private:
}; 

class SalesTicket : public Component
{
    public:
        SalesTicket ();            
        ~SalesTicket ();  
        void prtTicket();
    protected:
    private:
}; 

class TicketDecrator : public Component

{
    public:
        TicketDecrator (Component*);
        ~TicketDecrator ();      
        void callTrailer();
    protected:
    private:
        Component *myTrailer;
}; 


class Header1 : public TicketDecrator
{
    public:
        Header1 (Component*);     
        ~Header1 ();   
        void prtTicket();
    protected:
    private:
}; 

class Header2 : public TicketDecrator
{
    public:
        Header2 (Component*);     
        ~Header2 ();   
        void prtTicket();
    protected:
    private:
}; 

class Footer1 : public TicketDecrator
{
    public:
        Footer1 (Component*);     
        ~Footer1 ();   
        void prtTicket();
    protected:
    private:
}; 

class Footer2 : public TicketDecrator
{
    public:
        Footer2 (Component*);     
        ~Footer2 ();   
        void prtTicket();
    protected:
    private:
}; 



#endif   
