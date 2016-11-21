#ifndef DESCRIPTIONVISITOR_H
#define DESCRIPTIONVISITOR_H
#include "MediaVisitor.h"
#include <string>

class DescriptionVisitor :public MediaVisitor
{
public:
    virtual void visitShapeMedia(ShapeMedia *sm);
    virtual void visitComboMedia(ComboMedia *cm) {};
    virtual void visitComboMedia(ComboMedia *cm, bool start);
//    virtual void visitComboMediaPre(ComboMedia *cm);
//    virtual void visitComboMediaPost(ComboMedia *cm);

    DescriptionVisitor (): desc(std::string("")) {}
    std::string  getDescription() const {
        return desc;
    }
private:
    std::string desc;
};

#endif // DESCRIPTIONVISITOR_H
