#include "Circle.h"
Circle::Circle(Drawing* aDrawing, double x, double y, double r): Shape(aDrawing)
{
    _x = x;
    _y = y;
    _r = r;
}

Circle::~Circle() {}

void Circle::draw()
{
    drawCircle(_x, _y, _r);
}

