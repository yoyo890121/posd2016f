#include "ComboMediaBuilder.h"
#include "ComboMedia.h"
#include "ShapeMedia.h"

void ComboMediaBuilder::buildComboMedia() {combo = new ComboMedia;}
void ComboMediaBuilder::buildShapeMedia(Shape * s)
{
    if(!combo)
        throw std::string("null point ex");
    combo->add(new ShapeMedia(s));
}

void ComboMediaBuilder::buildAddComboMedia(Media * m) {combo->add(m);}

Media * ComboMediaBuilder::getMedia() {return combo;}
