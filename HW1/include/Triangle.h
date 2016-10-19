#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"


class Triangle : public Shape
{
public:
    Triangle(double pointAX,double pointAY,double pointBX,double pointBY,double pointCX,double pointCY);
    double area() const;
    double perimeter() const;
    void calcSideLength();

private:
    double pAX,pAY,pBX,pBY,pCX,pCY;
    double sAB,sBC,sAC;
    bool isTriangle();
};

#endif // TRIANGLE_H
