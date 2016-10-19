#ifndef MEDIAVISITOR_H
#define MEDIAVISITOR_H

class ShapeMedia;
class ComboMedia;

class MediaVisitor
{
    public:
    virtual void visitShapeMedia(ShapeMedia *sm)=0;
    virtual void visitComboMedia(ComboMedia *cm)=0;

    private:
};

#endif // MEDIAVISITOR_H
