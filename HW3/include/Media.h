#ifndef MEDIA_H
#define MEDIA_H
#include "DescriptionVisitor.h"
#include "AreaVisitor.h"
#include "PerimeterVisitor.h"



class Media {
public :
    virtual double area() const = 0 ;
    virtual double perimeter() const =0;
    virtual void accept(MediaVisitor*) =0;
    virtual void add(Media * m) {
        throw std::string("Illegal: add on media");
    }
};

#endif // MEDIA_H
