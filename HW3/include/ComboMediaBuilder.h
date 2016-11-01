#ifndef COMBOMEDIABUILDER_H
#define COMBOMEDIABUILDER_H

#include "MediaBuilder.h"

class ComboMediaBuilder : public MediaBuilder
{
public:
    void buildComboMedia();
    void buildShapeMedia(Shape * s);
    void buildAddComboMedia(Media * m);
    Media *getMedia();
private:
    ComboMedia * combo;
    ShapeMedia * smedia;
};

#endif // COMBOMEDIABUILDER_H
