#include "SalesOrder.h"
SalesOrder::SalesOrder(){}

SalesOrder::~SalesOrder(){}

void SalesOrder::process(CalcTax* TaxToUse)
{
    long itemNumber = 0;
    double price = 0.0;
    double dtax = TaxToUse->taxAmount(itemNumber, price);
}

