#include "Strategy.h"

int main ( int argc, char *argv[] )
{
    Strategy* pStrategy = new ConcreateStrageA();
    Context* pContext = new Context(pStrategy);
    pContext->ContextInterface();
    delete pContext;
    return 0;
}			/* ----------  end of function main  ---------- */

