#include "Component.h"
#include "Composite.h"
#include "Leaf.h"

int main ( int argc, char *argv[] )
{

    Leaf *l = new Leaf();
    l->Operation();
    Composite* com = new Composite();
    com->Add(l);
    com->Operation();
    Component* ll = com->GetChild(0);
    ll->Operation();
    return 0;
}			/* ----------  end of function main  ---------- */

