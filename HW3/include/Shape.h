#ifndef SHAPE_H
#define SHAPE_H
#include <vector>
#include <string>

class Shape
{
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string description() const =0;
};

double sumOfArea(const std::vector<Shape *> &shapes);
double sumOfPerimeter(const std::vector<Shape *> &shapes);

Shape* maxArea(const std::vector<Shape *> &shapes);
void sortByDecreasingPerimeter(std::vector<Shape *> &shapes);
#endif // SHAPE_H
