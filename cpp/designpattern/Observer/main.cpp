#include "Subject.h"
#include "Observer.h"

int main ( int argc, char *argv[] )
{
    ConcreteSubject* sub = new ConcreteSubject();
    Observer* o1 = new ConcreteObserverA(sub);
    Observer* o2 = new ConcreteObserverB(sub);
    sub->setState("old");
    sub->notify();
    sub->setState("new");
    sub->notify();

    delete o1;
    delete o2;
    delete sub;
    return 0;
}			/* ----------  end of function main  ---------- */

