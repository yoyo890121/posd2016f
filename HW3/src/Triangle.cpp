#include "Triangle.h"
#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;

Triangle::Triangle(double pointAX,double pointAY,double pointBX,double pointBY,double pointCX,double pointCY):
    pAX(pointAX),pAY(pointAY),pBX(pointBX),pBY(pointBY),pCX(pointCX),pCY(pointCY) {
    calcSideLength();
    if(!isTriangle()) {
        throw std::string("NOT a triangle");
    }
}

double Triangle::area() const {
    double s=(sAB+sAC+sBC)/2;
    return sqrt(s*(s-sAB)*(s-sAC)*(s-sBC));
}

double Triangle::perimeter() const {
    return sAB+sAC+sBC;
}

void Triangle::calcSideLength() {
    sAB=sqrt((pBX-pAX)*(pBX-pAX)+(pBY-pAY)*(pBY-pAY));
    sAC=sqrt((pCX-pAX)*(pCX-pAX)+(pCY-pAY)*(pCY-pAY));
    sBC=sqrt((pCX-pBX)*(pCX-pBX)+(pCY-pBY)*(pCY-pBY));
}

bool Triangle::isTriangle() {
    if((sAB+sAC>sBC)&&(sAC+sBC>sAB)&&(sBC+sAB>sAC))
        return true;
    else return false;
}

std::string Triangle::description() const {
    std::stringstream ss;
    ss << "t(" << pAX << " " << pAY << " " << pBX << " " << pBY <<" "<< pCX <<" "<< pCY << ") ";
    return ss.str();
}
