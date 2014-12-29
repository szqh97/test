#ifndef _Composite_h_
#define _Composite_h_
#include "Component.h"
#include <vector>
using namespace std;

class Composite: public Component
{
    public:
        Composite ();  
        ~Composite (); 
        void Operation();
        void Add(Component* com);
        void Remove(Component* com);
        Component* GetChild(int index);

    protected:

    private:
        vector<Component*> comVec;

}; /* -----  end of class Composite  ----- */

#endif
