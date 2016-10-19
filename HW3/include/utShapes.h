#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\..\cppunitlite\TestHarness.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Shape.h"
#include "ShapeMedia.h"
#include "ComboMedia.h"
#include <vector>
#include <iostream>

using namespace std;
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

TEST(Illegal,Triangle)
{
    try {
        Triangle tri(0,0,0,1,0,2);
        FAIL("should not be here");
    } catch(std::string s) {
        CHECK(std::string("NOT a triangle") == s);
    }
}

//6. Computing the sum of perimeters of a number of shapes, including at least one of each of rectangle, circle and triangle
TEST (fifth, sumOfArea)
{
    Rectangle r1(0,0,4,2); //area=8, perimeter=12
    Circle c1(0,0,10); //area=300, perimeter=60
    Triangle t1(0,0,0,3,4,0); //area=6 ,perimeter=12
    std::vector<Shape *> ss; //�Ϋ��Х��]
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    DOUBLES_EQUAL(314,sumOfArea(ss),epsilon);
    DOUBLES_EQUAL(84,sumOfPerimeter(ss),epsilon);
}

//HW2
//1. maxArea
TEST(first, maxArea)
{
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,0,3,4,0);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    DOUBLES_EQUAL(300,maxArea(ss)->area(),epsilon);
}

//2. sortByDecreasingPerimeter
TEST(second,sortByDecreasingPerimeter)
{
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

    /*
    cout <<"sortByDecreasingPerimeter:"<<endl;
    cout <<"Perimeter"<<"\t"<<"Area"<<endl;
    for(Shape *s:ss) {
        cout << s->perimeter() <<"\t"<< s->area() <<endl;
    }
    */
}

//3. Compose rTall and cSmall into a new shape, compute perimeter.
//4. Compose rTall and cSmall into a new shape, compute area.
// separate ComboShape into ComboMedia and Shape
/*
TEST(addShape,combo)
{
    Rectangle rTall(1,10,2,8); //area=16 ,perimeter=20
    Circle cSmall(2,1,1); //area=3 ,perimeter=6
    std::vector<Shape *> ss {&rTall};
    ComboShape cShape(ss);
    cShape.add(&cSmall);
    DOUBLES_EQUAL(26,cShape.perimeter(),epsilon);
    DOUBLES_EQUAL(19,cShape.area(),epsilon);
}
*/

TEST ( seven, media )
{
    Rectangle r1(0,0,4,2);
    ShapeMedia sR1( &r1 ) ;
    DOUBLES_EQUAL(8,sR1.area(),epsilon);
}

TEST ( eight, comboMedia )
{
    Rectangle r1(0,0,4,2);
    Rectangle r2(0,0,4,3);
    ShapeMedia sR1( &r1 ) ;
    ShapeMedia sR2( &r2 ) ;
    std::vector<Media *> ss{&sR1,&sR2};
    ComboMedia cm(ss);
    DOUBLES_EQUAL(20,cm.area(),epsilon) ;
}


TEST (ShapeMedia, DescriptionVisitor)
{
    Rectangle r1(0,0,4,2);
    ShapeMedia sR1( &r1 ) ;
    DescriptionVisitor dv;
    sR1.accept(&dv);
    //cout <<dv.getDescription()<<endl;
    CHECK(std::string("r(0 0 4 2) ") == dv.getDescription());
}


TEST (ComboMedia, DescriptionVisitor)
{
    Rectangle r1(0,0,4,2);
    Circle r2(0,0,10);
    ShapeMedia sR1( &r1 ) ;
    ShapeMedia sR2( &r2 ) ;
    std::vector<Media *> ss{&sR1,&sR2};
    ComboMedia cm(ss);
    DescriptionVisitor dv;
    cm.accept(&dv);
    //cout <<dv.getDescription()<<endl;
    CHECK(std::string("combo(r(0 0 4 2) c(0 0 10) )") == dv.getDescription());
}


TEST (IllegalAdd, ShapeMedia)
{
    Rectangle r1(0,0,4,2);
    Circle r2(0,0,10);
    ShapeMedia sR1( &r1 ) ;
    ShapeMedia sR2( &r2 ) ;
    try {
        sR1.add(&sR2);
        FAIL("should not be here");
    } catch(std::string s) {
        CHECK(std::string("Illegal: add on media") == s);
    }
}

//HW3
//1. Regular hexagon
TEST (RegularHexagon, ComboMedia)
{
    Rectangle r1(0,2*sqrt(3),2*sqrt(3),2);
    Triangle t1(0,0,-1,sqrt(3),0,2*sqrt(3));
    Triangle t2(2,0,3,sqrt(3),2,2*sqrt(3));
    ShapeMedia sR1(&r1);
    ShapeMedia sT1(&t1);
    ShapeMedia sT2(&t2);
    std::vector <Media*> mSR1{&sR1};
    ComboMedia cMSR1(mSR1);
    cMSR1.add(&sT1);
    //cm.add(&sT!);
    //cm.add(&sT2);
    std::vector <Media*> mST2{&sT2};
    ComboMedia cm(mST2);
    cm.add(&cMSR1);
    cout <<"area="<<cm.area()<<endl;
    cout <<"perimeter="<<cm.perimeter()<<endl;
    DOUBLES_EQUAL((3.0/2.0*2*2*sqrt(3)),cm.area(),epsilon);
    DOUBLES_EQUAL(2*6+2*sqrt(3)*4,cm.perimeter(),epsilon);

    DescriptionVisitor dv;
    cm.accept(&dv);
    cout <<dv.getDescription()<<endl;

    //2. AreaVisitor
    AreaVisitor av;
    cm.accept(&av);
    //cout<<av.getArea()<<endl;
    DOUBLES_EQUAL(cm.area(),av.getArea(),epsilon);
    //3. PerimeterVisitor
    PerimeterVisitor pv;
    cm.accept(&pv);
    DOUBLES_EQUAL(cm.perimeter(),pv.getPerimeter(),epsilon);
}

#endif // UTSHAPES_H_INCLUDED