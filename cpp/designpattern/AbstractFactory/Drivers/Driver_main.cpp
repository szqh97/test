#include "AppControl.h"


int main ( int argc, char *argv[] )
{
    AppControl* ap = new AppControl(0);
    ap->doDraw();
    ap->doPrint();
    delete ap;
    return 0;
}			/* ----------  end of function main  ---------- */

