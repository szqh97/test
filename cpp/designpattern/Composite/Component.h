
#ifndef  _Component_H_
#define  _Component_H_

class Component
{
    public:
        Component ();
        virtual ~Component();

        virtual void Operation() = 0;
        virtual void Add(Component*);
        virtual void Remove(Component*);
        virtual Component* GetChild(int);
    protected:

    private:

}; /* -----  end of class Component  ----- */

#endif   /* ----- #ifndef _Component_H_  ----- */
