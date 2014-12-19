 
#include "builder.h"
#include "direct.h"
#include "Product.h"
int main ( int argc, char *argv[] )
{
    Builder_KindOne *b1 = new Builder_KindOne();
    Director d ;
    d.construct(b1);
    Product *p = b1->getProduct();
    p->showProduct();

    delete p;
    delete b1;

    return 0;
}			/* ----------  end of function main  ---------- */

