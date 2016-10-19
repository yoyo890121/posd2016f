#include "PerimeterVisitor.h"
#include "ShapeMedia.h"
#include "ComboMedia.h"
#include <iostream>

void PerimeterVisitor::visitShapeMedia(ShapeMedia *sm)
{
    std::cout <<"ShapePerimeter="<<sm->getShape()->perimeter()<<std::endl;
    perimeter+=sm->getShape()->perimeter();
}

void PerimeterVisitor::visitComboMedia(ComboMedia *cm)
{
    std::cout <<"ComboPerimeter="<<cm->perimeter()<<std::endl;
}

