#include "DescriptionVisitor.h"
#include "ShapeMedia.h"

void DescriptionVisitor::visitShapeMedia(ShapeMedia *sm) {
    desc += sm->getShape()->description();
}


void DescriptionVisitor::visitComboMedia(ComboMedia *cm, bool start) {
    if(start)
        desc = desc + std::string("combo(");
    else
        desc = desc + std::string(")");
}
