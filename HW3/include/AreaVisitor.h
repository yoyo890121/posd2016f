#ifndef AREAVISITOR_H
#define AREAVISITOR_H

#include "MediaVisitor.h"

class AreaVisitor : public MediaVisitor
{
public:
    virtual void visitShapeMedia(ShapeMedia *sm);
    virtual void visitComboMedia(ComboMedia *cm);
    AreaVisitor() {}
    double getArea() const {
        return area;
    }

private:
    double area=0;
};

#endif // AREAVISITOR_H
