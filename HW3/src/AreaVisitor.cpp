#include "AreaVisitor.h"
#include "ShapeMedia.h"
#include "ComboMedia.h"
#include <iostream>

void AreaVisitor::visitShapeMedia(ShapeMedia *sm)
{
    std::cout <<"ShapeArea="<<sm->getShape()->area()<<std::endl;
    area+=sm->getShape()->area();
}

void AreaVisitor::visitComboMedia(ComboMedia *cm)
{
    std::cout <<"ComboArea="<<cm->area()<<std::endl;
}
