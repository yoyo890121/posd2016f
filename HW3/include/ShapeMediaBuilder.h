#ifndef SHAPEMEDIABUILDER_H
#define SHAPEMEDIABUILDER_H

#include "MediaBuilder.h"


class ShapeMediaBuilder : public MediaBuilder
{
public:
    void buildComboMedia() {}
    void buildShapeMedia(Shape * s);
    virtual void buildAddComboMedia(Media * m){};
    Media *getMedia();
private:
    ShapeMedia * smedia;
};

#endif // SHAPEMEDIABUILDER_H
