#ifndef TEXTMEDIA_H
#define TEXTMEDIA_H
#include <string>
#include "Media.h"
#include "Rectangle.h"
#include "Shape.h"
class TextMedia : public Media
{
public:
    TextMedia(Rectangle* boundingBox,std::string text);
    Rectangle* getBoundingBox() {return r;}
    std::string getText() {return s;}

    double area() const{return r->area();}
    double perimeter() const {return r->perimeter();}
    void accept(MediaVisitor* mv) {}
private:
    Rectangle* r;
    std::string s;
};

#endif // TEXTMEDIA_H
