#ifndef SHAPEMEDIA_H
#define SHAPEMEDIA_H
#include "Shape.h"
#include "Media.h"

class ShapeMedia :public Media
{
private:
    Shape* shape ;
public :
    ShapeMedia( Shape* s ): shape(s) {}
    virtual void accept(MediaVisitor * mv);
    double area() const;
    double perimeter() const;
    Shape* getShape()const;
};

#endif // SHAPEMEDIA_H
