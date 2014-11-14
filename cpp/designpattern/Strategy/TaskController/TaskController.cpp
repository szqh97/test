#include "TaskController.h"
#include "SalesOrder.h"
#include "CanTax.h"
#include "USTax.h"
#include <iostream>

TaskController::TaskController(){}

TaskController::~TaskController(){}
void TaskController::process(int zipcode)
{
    CalcTax *myTax;
    SalesOrder *mySO = new SalesOrder();
    myTax = getTaxRules4Country(zipcode);
    mySO->process(myTax);
    releaseCalcTax(myTax);
    delete mySO;
    mySO=NULL;
}

CalcTax* TaskController::getTaxRules4Country(int ZipCode)
{
    if (ZipCode == 0)
    {
        return new USTax;
    }
    else if (ZipCode == 1)
    {
        return new CanTax;
    }
}

void TaskController::releaseCalcTax(CalcTax* pcal)
{
    if (pcal)
    {
        delete pcal;
        pcal = NULL;
    }
}
