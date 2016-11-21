#ifndef COMBOMEDIA_H
#define COMBOMEDIA_H
#include <vector>
#include <algorithm>
#include "Media.h"


class ComboMedia : public Media {
private:
    std::vector<Media*> media;
public:
    ComboMedia () {}
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
        mv->visitComboMedia(this, true);
        for (Media *m: media)
            m->accept(mv);
        mv->visitComboMedia(this, false);
    }

    void add (Media *m) {
        media.push_back(m);
    }

//    void removeMedia (Media *m) {
//        for (auto it=media.begin() ;it!=media.end();++it)
//        {
//            if(*it==m)
//            {
//                media.erase(it);
//                break;
//            }
//        }
//    }

    void removeMedia(Media *m) {
        DescriptionVisitor dv;
        m->accept(&dv);
        int index = 0;
        for(Media *fm:media) {
            try {
                DescriptionVisitor dv2;
                fm->accept(&dv2);
                if(dv.getDescription()==dv2.getDescription())
                    media.erase(media.begin()+index);
                else
                    fm->removeMedia(m);
            } catch(std::string error) {
                DescriptionVisitor dv2;
                fm->accept(&dv2);
                if(dv.getDescription()==dv2.getDescription())
                    media.erase(media.begin()+index);
            }
            index++;
        }
    }

};

#endif // COMBOMEDIA_H
