#include "ShapeMediaBuilder.h"
#include "ShapeMedia.h"
#include "ComboMedia.h"

void ShapeMediaBuilder::buildShapeMedia(Shape * s)
{
    smedia = new ShapeMedia(s);
    smedia->getShape();
}

Media *ShapeMediaBuilder::getMedia() {return smedia;}
