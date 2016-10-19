#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\..\cppunitlite\TestHarness.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Shape.h"
#include "ComboShape.h"
#include <vector>
#include <iostream>

const double epsilon = 0.000001;

//HW1
//1. Computing  the perimeter of a circle
TEST(first,Circle)
{
    Circle circ(0,0,10);
    DOUBLES_EQUAL(300,circ.area(),epsilon);
    DOUBLES_EQUAL(60,circ.perimeter(),epsilon);
}

//2. Computing  the perimeter of a rectangle
TEST(second, Rectangle)
{
    Rectangle rect(0,0,4,2);
    DOUBLES_EQUAL(8,rect.area(),epsilon);
    DOUBLES_EQUAL(12,rect.perimeter(),epsilon);
}

//3. Creating a triangle given three points
//4. Computing  the perimeter of a triangle
//5. Computing  the area of a triangle
TEST(third,Triangle)
{
    Triangle tri(0,0,0,3,4,0);
    DOUBLES_EQUAL(6,tri.area(),epsilon);
    DOUBLES_EQUAL(12,tri.perimeter(),epsilon);
}

TEST(forth,Triangle)
{
    Triangle tri(0,0,0,1,0,2);
    DOUBLES_EQUAL(0,tri.area(),epsilon);
    DOUBLES_EQUAL(4,tri.perimeter(),epsilon);
}

//6. Computing the sum of perimeters of a number of shapes, including at least one of each of rectangle, circle and triangle
TEST (fifth, sumOfArea) {
    Rectangle r1(0,0,4,2); //area=8, perimeter=12
    Circle c1(0,0,10); //area=300, perimeter=60
    Triangle t1(0,0,0,3,4,0); //area=6 ,perimeter=12
    std::vector<Shape *> ss; //用指標打包
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    DOUBLES_EQUAL(314,sumOfArea(ss),epsilon);
    DOUBLES_EQUAL(84,sumOfPerimeter(ss),epsilon);
}

//HW2
//1. maxArea
TEST(first, maxArea) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,0,3,4,0);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);

    DOUBLES_EQUAL(300,maxArea(ss)->area(),epsilon);
    cout <<"maxArea="<<maxArea(ss)->area()<<endl;
}

//2. sortByDecreasingPerimeter
TEST(second,sortByDecreasingPerimeter) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,0,3,4,0);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);

    sortByDecreasingPerimeter(ss);

    std::vector<Shape *> sorted{&c1,&r1,&t1};
    CHECK(ss==sorted);

    cout <<"sortByDecreasingPerimeter:"<<endl;
    cout <<"Perimeter"<<"\t"<<"Area"<<endl;
    for(Shape *s:ss) {
        cout << s->perimeter() <<"\t"<< s->area() <<endl;
    }
}

//3. Compose rTall and cSmall into a new shape, compute perimeter.
//4. Compose rTall and cSmall into a new shape, compute area.
TEST(addShape,combo) {
    Rectangle rTall(1,10,2,8); //area=16 ,perimeter=20
    Circle cSmall(2,1,1); //area=3 ,perimeter=6
    std::vector<Shape *> ss {&rTall};
    ComboShape cShape(ss);
    cShape.add(&cSmall);
    DOUBLES_EQUAL(26,cShape.perimeter(),epsilon);
    DOUBLES_EQUAL(19,cShape.area(),epsilon);
}

#endif // UTSHAPES_H_INCLUDED
