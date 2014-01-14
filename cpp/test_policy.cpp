#include "Creator_policy.h"
using namespace std;
typedef struct
{
    int a;
    int b;
}IntPair;
template <class CreattionPolicy>
class widgetManager: public CreattionPolicy
{};

typedef widgetManager< OpNewCreator<IntPair> > myWidgetMgr;

template < template <class creatPolicy> class cp>
class wdManager : public cp<IntPair>
{
    void SwithPrototype(IntPair* pNewPrototype)
    {
        cp<IntPair>& myPolicy = *this;
        delete myPolicy.GetPrototype();
        myPolicy.SetPrototype(pNewPrototype);
    }
};

typedef wdManager<PrototypeCreator> myWdMgr;

int main ( int argc, char *argv[] )
{
    myWidgetMgr m;
    cout << sizeof(m) << endl;
    myWdMgr mym;
    cout << sizeof(mym) << endl;
    IntPair *p = new IntPair;
    mym.SetPrototype(p);
    //mym.SetPrototype(p);
    
    delete p;

    return 0;
}			/* ----------  end of function main  ---------- */

