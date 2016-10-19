#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"


class Circle : public Shape
{
public:
    Circle(double centerX,double centerY,double radius);
    const double PI=3;
    double area() const;
    double perimeter() const;
private:
    double cx;
    double cy;
    double r;
};

#endif // CIRCLE_H
