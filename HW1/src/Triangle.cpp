#include "Triangle.h"
#include <math.h>
#include <iostream>
using namespace std;
Triangle::Triangle(double pointAX,double pointAY,double pointBX,double pointBY,double pointCX,double pointCY):
    pAX(pointAX),pAY(pointAY),pBX(pointBX),pBY(pointBY),pCX(pointCX),pCY(pointCY)
{
    calcSideLength();
    if(!isTriangle())
    {
        cout <<"("<<pAX<<","<<pAY<<") ";
        cout <<"("<<pBX<<","<<pBY<<") ";
        cout <<"("<<pCX<<","<<pCY<<") ";
        cout <<"NOT a triangle"<<endl;
    }
}

double Triangle::area() const
{
    double s=(sAB+sAC+sBC)/2;
    return sqrt(s*(s-sAB)*(s-sAC)*(s-sBC));
}

double Triangle::perimeter() const
{
    return sAB+sAC+sBC;
}

void Triangle::calcSideLength()
{
    sAB=sqrt((pBX-pAX)*(pBX-pAX)+(pBY-pAY)*(pBY-pAY));
    sAC=sqrt((pCX-pAX)*(pCX-pAX)+(pCY-pAY)*(pCY-pAY));
    sBC=sqrt((pCX-pBX)*(pCX-pBX)+(pCY-pBY)*(pCY-pBY));
}

bool Triangle::isTriangle()
{
    if((sAB+sAC>sBC)&&(sAC+sBC>sAB)&&(sBC+sAB>sAC))
        return true;
    else return false;
}
