#include "DescriptionVisitor.h"
#include "ShapeMedia.h"

void DescriptionVisitor::visitShapeMedia(ShapeMedia *sm)
{
    desc += sm->getShape()->description();
}

void DescriptionVisitor::visitComboMedia(ComboMedia *cm)
{
    desc = std::string("combo(")+desc+std::string(")");
}
