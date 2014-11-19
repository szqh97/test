#include "Decrator.h"
#include <iostream>
using namespace std;

int main ( int argc, char *argv[] )
{
    SalesTicket* ticket = new SalesTicket();
    TicketDecrator* pdec = new Footer1(ticket);
    pdec = new Footer2(pdec);
    pdec = new Header1(pdec);
    pdec = new Header2(pdec);
    pdec->prtTicket();
    delete pdec;

    return 0;
}			/* ----------  end of function main  ---------- */
