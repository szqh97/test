#include "Creator_policy.h"
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
{};

typedef wdManager<OpNewCreator> myWdMgr;

int main ( int argc, char *argv[] )
{
    myWidgetMgr m;
    myWdMgr k;
    IntPair *p = new IntPair;
    
    delete p;

    return 0;
}			/* ----------  end of function main  ---------- */

