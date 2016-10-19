#ifndef SHAPE_H
#define SHAPE_H
#include <vector>
using namespace std;

class Shape
{
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};

double sumOfArea(const vector<Shape *> &shapes);
double sumOfPerimeter(const vector<Shape *> &shapes);

Shape* maxArea(const vector<Shape *> &shapes);
void sortByDecreasingPerimeter(vector<Shape *> &shapes);
#endif // SHAPE_H
