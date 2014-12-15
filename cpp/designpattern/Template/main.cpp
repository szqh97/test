#include "Template.h"


int main ( int argc, char *argv[] )
{
    AbstractClass* p1 = new ConcreteClass1();
    AbstractClass* p2 = new ConcreteClass2();
    p1->TemplateMethod();
    p2->TemplateMethod();
    delete p1;
    delete p2;
    return 0;
}			/* ----------  end of function main  ---------- */

