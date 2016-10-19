#ifndef COMBOSHAPE_H
#define COMBOSHAPE_H

#include "Shape.h"


class ComboShape : public Shape
{
    public:
        ComboShape(const std::vector<Shape *> &shapes);
        double area() const {return sumOfArea(shapes);}
        double perimeter() const {return sumOfPerimeter(shapes);}
        void add(Shape * shape) {shapes.push_back(shape);}
    private:
        std::vector<Shape*> shapes;
};

#endif // COMBOSHAPE_H
