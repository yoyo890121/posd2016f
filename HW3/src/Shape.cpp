#include "Shape.h"
#include <algorithm>
using std::vector;

double sumOfArea(const vector<Shape *> &shapes)
{
    double total =0;
    for (Shape *s: shapes)
        total += s->area();
    return total;
}

double sumOfPerimeter(const vector<Shape *> &shapes)
{
    double total =0;
    for (Shape *s:shapes)
        total+=s->perimeter();
    return total;
}

bool compArea(const Shape *a,const Shape *b)
{
    return a->area() < b->area();
}

Shape* maxArea(const vector<Shape *> &shapes)
{
    return *max_element(shapes.begin(),shapes.end(),compArea);
}

bool compPerimeter(const Shape *a,const Shape *b)
{
    //if(a->perimeter() == b->perimeter()) return a->area() < b->area();
    return a->perimeter() > b->perimeter();
}

void sortByDecreasingPerimeter(vector<Shape *> &shapes)
{
    sort(shapes.begin(),shapes.end(),compPerimeter);
}
