#include "Flyweight.h"
#include "FlyweightFactory.h"

int main ( int argc, char *argv[] )
{
    FlyweightFactory* fc = new FlyweightFactory();

    Flyweight* fw1 = fc->GetFlyweight("hello");
    Flyweight* fw2 = fc->GetFlyweight("world");
    Flyweight* fw3 = fc->GetFlyweight("hhhh");

    delete fw1;
    delete fw2;
    delete fw3;
    delete fc;
    return 0;
}			/* ----------  end of function main  ---------- */
