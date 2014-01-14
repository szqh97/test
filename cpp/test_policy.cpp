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

int main ( int argc, char *argv[] )
{
    myWidgetMgr m;

    return 0;
}			/* ----------  end of function main  ---------- */

