#include "direct.h"

Director::Director(){}

void Director::construct(Builder *b)
{
    b->buildPartHead("red");
    b->buildPartBody("kk");
    b->buildPartFoot("kkk");
    std::cout << "Build all parts of product ..." << std::endl;

}

