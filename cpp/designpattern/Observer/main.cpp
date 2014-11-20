#include "Subject.h"
#include "Observer.h"

int main ( int argc, char *argv[] )
{
    ConcreteSubject* sub = new ConcreteSubject();
    ConcreteObserverA* o1 = new ConcreteObserverA(sub);
    ConcreteObserverB* o2 = new ConcreteObserverB(sub);
    sub->setState("old");
    sub->notify();
    sub->setState("new");
    sub->notify();

    delete sub;
    delete o1;
    delete o2;
    return 0;
}			/* ----------  end of function main  ---------- */

