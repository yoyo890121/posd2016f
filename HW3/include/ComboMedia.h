#ifndef COMBOMEDIA_H
#define COMBOMEDIA_H
#include <vector>
#include "Media.h"


class ComboMedia : public Media {
private:
    std::vector<Media*> media;
public:
    ComboMedia( std::vector<Media*> m ) : media(m) {}
    double area() const {
        double total =0;
        for (Media *m: media)
            total += m->area();
        return total;
    }

    double perimeter() const {
        double total=0;
        for (Media *m:media)
            total += m->perimeter();
        return total;
    }

    void accept(MediaVisitor *mv) {
        for (Media *m: media)
            m->accept(mv);
        mv->visitComboMedia(this);
    }

    void add (Media *m) {
        media.push_back(m);
    }
};

#endif // COMBOMEDIA_H
