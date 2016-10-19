#include "Circle.h"

Circle::Circle(double centerX,double centerY,double radius):
    cx(centerX),cy(centerY),r(radius) {};

double Circle::area() const
{
    return PI*r*r;
}

double Circle::perimeter() const
{
    return 2*PI*r;
}
