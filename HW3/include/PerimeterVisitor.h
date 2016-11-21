#ifndef PERIMETERVISITOR_H
#define PERIMETERVISITOR_H

#include "MediaVisitor.h"


class PerimeterVisitor : public MediaVisitor
{
public:
    virtual void visitShapeMedia(ShapeMedia *sm);
    virtual void visitComboMedia(ComboMedia *cm);
    PerimeterVisitor() {}
    double getPerimeter() const {
        return perimeter;
    }

private:
    double perimeter=0;
};

#endif // PERIMETERVISITOR_H
