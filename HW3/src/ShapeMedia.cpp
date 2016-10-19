#include "ShapeMedia.h"

void ShapeMedia::accept(MediaVisitor * mv)
{
    mv->visitShapeMedia(this);
}
double ShapeMedia::area() const
{
    return shape->area() ;
}
double ShapeMedia::perimeter() const
{
    return shape->perimeter() ;
}
Shape* ShapeMedia::getShape()const
{
    return shape;
}
