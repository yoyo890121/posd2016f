#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\..\cppunitlite\TestHarness.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "ShapeMedia.h"
#include "ComboMedia.h"
#include "ShapeMediaBuilder.h"
#include "ComboMediaBuilder.h"
#include "TextMedia.h"
#include "Document.h"
#include "MyDocument.h"
#include "MediaDirector.h"
#include "TextUI.h"
#include "CommandManager.h"
#include "AddCommand.h"
#include "DefCommand.h"
#include "DeleteCommand.h"
#include <vector>
#include <iostream>

using namespace std;
const double epsilon = 0.000001;

//HW1
//1. Computing  the perimeter of a circle
TEST(first,Circle) {
    Circle circ(0,0,10);
    DOUBLES_EQUAL(300,circ.area(),epsilon);
    DOUBLES_EQUAL(60,circ.perimeter(),epsilon);
}

//2. Computing  the perimeter of a rectangle
TEST(second, Rectangle) {
    Rectangle rect(0,0,4,2);
    DOUBLES_EQUAL(8,rect.area(),epsilon);
    DOUBLES_EQUAL(12,rect.perimeter(),epsilon);
}

//3. Creating a triangle given three points
//4. Computing  the perimeter of a triangle
//5. Computing  the area of a triangle
TEST(third,Triangle) {
    Triangle tri(0,0,0,3,4,0);
    DOUBLES_EQUAL(6,tri.area(),epsilon);
    DOUBLES_EQUAL(12,tri.perimeter(),epsilon);
}

TEST(Illegal,Triangle) {
    try {
        Triangle tri(0,0,0,1,0,2);
        FAIL("should not be here");
    } catch(std::string s) {
        CHECK(std::string("NOT a triangle") == s);
    }
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

TEST(addShape,combo) {
    Rectangle rTall(1,10,2,8); //area=16 ,perimeter=20
    ShapeMedia sR1(&rTall) ;
    Circle cSmall(2,1,1); //area=3 ,perimeter=6
    ShapeMedia sC1(&cSmall) ;
    std::vector<Media *> ss {&sR1};
    ComboMedia cShape(ss);
    cShape.add(&sC1);
    DOUBLES_EQUAL(26,cShape.perimeter(),epsilon);
    DOUBLES_EQUAL(19,cShape.area(),epsilon);
}


TEST ( seven, media ) {
    Rectangle r1(0,0,4,2);
    ShapeMedia sR1( &r1 ) ;
    DOUBLES_EQUAL(8,sR1.area(),epsilon);
}

TEST ( eight, comboMedia ) {
    Rectangle r1(0,0,4,2);
    Rectangle r2(0,0,4,3);
    ShapeMedia sR1( &r1 ) ;
    ShapeMedia sR2( &r2 ) ;
    std::vector<Media *> ss{&sR1,&sR2};
    ComboMedia cm(ss);
    DOUBLES_EQUAL(20,cm.area(),epsilon) ;
}

//DescriptionVisitor
TEST (ShapeMedia, DescriptionVisitor) {
    Rectangle r1(0,0,4,2);
    ShapeMedia sR1( &r1 ) ;
    DescriptionVisitor dv;
    sR1.accept(&dv);
    //cout <<dv.getDescription()<<endl;
    CHECK(std::string("r(0 0 4 2) ") == dv.getDescription());
}


TEST (ComboMedia, DescriptionVisitor) {
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


TEST (IllegalAdd, ShapeMedia) {
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
TEST (RegularHexagon, ComboMedia) {
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
    //cout <<"area="<<cm.area()<<endl;
    //cout <<"perimeter="<<cm.perimeter()<<endl;
    DOUBLES_EQUAL((3.0/2.0*2*2*sqrt(3)),cm.area(),epsilon);
    DOUBLES_EQUAL(2*6+2*sqrt(3)*4,cm.perimeter(),epsilon);

    DescriptionVisitor dv;
    cm.accept(&dv);
    //cout <<dv.getDescription()<<endl;
    CHECK(std::string("combo(t(2 0 3 1.73205 2 3.4641) combo(r(0 3.4641 3.4641 2) t(0 0 -1 1.73205 0 3.4641) ))") ==dv.getDescription());

    //DescriptionVisitor start issue
    /*
    //2. AreaVisitor
    AreaVisitor av;
    cm.accept(&av);
    //cout<<av.getArea()<<endl;
    DOUBLES_EQUAL(cm.area(),av.getArea(),epsilon);
    //3. PerimeterVisitor
    PerimeterVisitor pv;
    cm.accept(&pv);
    DOUBLES_EQUAL(cm.perimeter(),pv.getPerimeter(),epsilon);
    */
}

//MediaBuilder
#include <stack>
TEST (ComboMedia5, MediaBuilder) {
    std::stack<ComboMediaBuilder *> mbs;
    mbs.push(new ComboMediaBuilder());
    mbs.top()->buildComboMedia();

    Rectangle r(0,0,4,2);
    mbs.top()->buildShapeMedia(&r);
    Circle c(0,0,10);
    mbs.top()->buildShapeMedia(&c);

    mbs.push(new ComboMediaBuilder());
    mbs.top()->buildComboMedia();

    Rectangle r2(0,0,2,1);
    mbs.top()->buildShapeMedia(&r2);
    Circle c2(0,0,5);
    mbs.top()->buildShapeMedia(&c2);

    Media *cm = mbs.top()->getMedia();
    mbs.pop();
    mbs.top()->buildAddComboMedia(cm);

    DescriptionVisitor dv;
    mbs.top()->getMedia()->accept(&dv);
    //std::cout << dv.getDescription() << std::endl;

    CHECK(std::string("combo(r(0 0 4 2) c(0 0 10) combo(r(0 0 2 1) c(0 0 5) ))") == dv.getDescription());
}

//HW4
//1.
TEST (ShapeMediaBuilder, MediaBuilder) {
    ShapeMediaBuilder smb;
    Circle c(0,0,5);
    smb.buildShapeMedia(&c);

    Media * m=smb.getMedia();

    DescriptionVisitor dv;
    m->accept(&dv);
    //cout <<dv.getDescription()<<endl;
    CHECK(std::string("c(0 0 5) ") == dv.getDescription());
}

//2.
TEST (ComboMediaBuilder, MediaBuilder) {
    std::stack<ComboMediaBuilder *> cmbs;
    cmbs.push(new ComboMediaBuilder()); //combo(
    cmbs.top()->buildComboMedia();

    cmbs.push(new ComboMediaBuilder()); //combo(
    cmbs.top()->buildComboMedia();

    cmbs.push(new ComboMediaBuilder()); //combo(
    cmbs.top()->buildComboMedia();

    Rectangle r(10,0,15,5); //r(10 0 15 5)
    cmbs.top()->buildShapeMedia(&r);
    Circle c(12,5,2); //c(12 5 2)
    cmbs.top()->buildShapeMedia(&c);

    Media *cm1 = cmbs.top()->getMedia(); //)
    cmbs.pop();
    cmbs.top()->buildAddComboMedia(cm1);

    Rectangle r2(0,0,25,20); //r(0 0 25 20)
    cmbs.top()->buildShapeMedia(&r2);

    Media *cm2 = cmbs.top()->getMedia(); //)
    cmbs.pop();
    cmbs.top()->buildAddComboMedia(cm2);

    Triangle t(0,20,16,32,25,20); //t(0 20 16 32 25 20)
    cmbs.top()->buildShapeMedia(&t);

    Media *m=cmbs.top()->getMedia(); //)

    DescriptionVisitor dv;
    m->accept(&dv);
    //cout << dv.getDescription() << endl;

    CHECK(string("combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20) )") == dv.getDescription());
}

//3.
TEST (TextMedia, MediaBuilder) {
    Rectangle r(10,10,10,10);
    std::string s("Text123");
    TextMedia tm(&r,s);

    DOUBLES_EQUAL(100,tm.area(),epsilon);
    CHECK(string("Text123")==tm.getText());
}

//4.
TEST (removeMedia, MediaBuilder) {
    //Create Figure 1
    std::stack<ComboMediaBuilder *> cmbs;
    cmbs.push(new ComboMediaBuilder());
    cmbs.top()->buildComboMedia();

    cmbs.push(new ComboMediaBuilder());
    cmbs.top()->buildComboMedia();

    cmbs.push(new ComboMediaBuilder());
    cmbs.top()->buildComboMedia();

    Rectangle r(10,0,15,5);
    cmbs.top()->buildShapeMedia(&r);
    Circle c(12,5,2);
    cmbs.top()->buildShapeMedia(&c);

    Media *cm1 = cmbs.top()->getMedia();
    cmbs.pop();
    cmbs.top()->buildAddComboMedia(cm1);

    Rectangle r2(0,0,25,20);
    cmbs.top()->buildShapeMedia(&r2);

    Media *cm2 = cmbs.top()->getMedia();
    cmbs.pop();
    cmbs.top()->buildAddComboMedia(cm2);

    Triangle t(0,20,16,32,25,20);
    cmbs.top()->buildShapeMedia(&t);

    Media* m=cmbs.top()->getMedia();

    //Create end

    ShapeMedia deleteSM(&r2);
    m->removeMedia(&deleteSM);

    DescriptionVisitor dv;
    m->accept(&dv);
    //cout << dv.getDescription() << endl;
    CHECK(string("combo(combo(combo(r(10 0 15 5) c(12 5 2) ))t(0 20 16 32 25 20) )") == dv.getDescription());
}

//HW5
//1.
TEST (readFile, Document) {
    string myShapeString;
    Document* doc=new MyDocument();
    myShapeString=doc->openDocument("myShape.txt");
    CHECK(string("combo(r(0 0 3 2) c(0 0 5) combo(r(0 0 5 4) c(0 0 10) )combo(r(0 1 8 7) c(0 1 10) ))") == myShapeString);
}

TEST (notExistFile, Document) {
    string myShapeString;
    try {
        Document* doc=new MyDocument();
        myShapeString=doc->openDocument("a.txt");
        FAIL("should not be here");
    } catch (string s) {
        CHECK(std::string("file is not existed.") == s);
    }
}

//2.
TEST (Director, MediaDirector) {
    string myShapeString;
    Document* doc=new MyDocument();
    myShapeString=doc->openDocument("myShape.txt");
    MediaDirector md;
    md.concrete(myShapeString);
    std::stack<MediaBuilder *> mbs;
    md.setMediaBuilder(&mbs);
    Media *m=mbs.top()->getMedia();
    DescriptionVisitor dv;
    m->accept(&dv);
    //cout << dv.getDescription() << endl;
}

TEST (testString, MediaDirector) {
    string str("t(1 1 2 2 3 4)");
    MediaDirector md;
    md.concrete(str);
    std::stack<MediaBuilder *> mbs;
    md.setMediaBuilder(&mbs);
    Media *m=mbs.top()->getMedia();
    DescriptionVisitor dv;
    m->accept(&dv);
    //cout << dv.getDescription() << endl;
}


//HW6
//1.
//TEST (defCircle,TextUI)
//{
//    TextUI test;
//    string input("def cSmall = Circle(2,1,1)");
//    test.processCommand(input);
//}
//
//TEST (defRectangle,TextUI)
//{
//    TextUI test;
//    string input("def rTall = Rectangle(1,10,2,8)");
//    test.processCommand(input);
//}
//
//

//TEST (defComboMedia,TextUI)
//{
//    TextUI test;
//    test.processCommand("def cSmall = Circle(2,1,1)");
//    test.processCommand("def rTall = Rectangle(1,10,2,8)");
//    test.processCommand("def comboExclamation = combo{rTall,cSmall}");
//    test.processCommand("rTall.area?");
//    test.processCommand("comboExclamation.perimeter?");
//    test.processCommand("save comboExclamation to \"myShapes.txt\"");
//    test.processCommand("delete rTall from comboExclamation");
//    test.processCommand("show");
//    test.processCommand("delete rTall");
//    test.processCommand("show");
//    test.processCommand("def cMale = Circle(3,2,1)");
//    test.processCommand("add cMale to comboExclamation");
//}

//HW7

//4. definition
TEST (DefRectangle, DefCommand) {
    TextUI* application=new TextUI();
    DefCommand def(application);
    def.execute("r = Rectangle(0,0,10,10)");
    auto it=application->mediaList.find("r");
    DescriptionVisitor dv,dv2;
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv);
    }
    CHECK(string("r(0 0 10 10) ") == dv.getDescription());

    def.undo();
    it=application->mediaList.find("r");
    if(it!=application->mediaList.end()) {
        FAIL("Should not be here");
    }
    CHECK(application->mediaList.empty() == true);

    def.redo();
    it=application->mediaList.find("r");
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv2);
    }
    CHECK(string("r(0 0 10 10) ") == dv2.getDescription());
}

TEST (DefCombo, DefCommand) {
    TextUI* application=new TextUI();
    DefCommand def(application);
    def.execute("cSmall = Circle(2,1,1)");
    def.execute("rTall = Rectangle(1,10,2,8)");
    def.execute("comboExclamation = combo{rTall,cSmall}");
    auto it=application->mediaList.find("comboExclamation");
    DescriptionVisitor dv,dv2;
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv);
    }

    CHECK(string("combo(r(1 10 2 8) c(2 1 1) )") == dv.getDescription());
    LONGS_EQUAL(application->mediaList.size(), 3);

    def.undo();
    it=application->mediaList.find("comboExclamation");
    if(it!=application->mediaList.end()) {
        FAIL("Should not be here");
    }
    LONGS_EQUAL(application->mediaList.size(), 2);

    def.redo();
    it=application->mediaList.find("comboExclamation");
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv2);
    }
    CHECK(string("combo(r(1 10 2 8) c(2 1 1) )") == dv2.getDescription());
    LONGS_EQUAL(application->mediaList.size(), 3);
}

//3. add
TEST(Add, AddCommand) {
    TextUI* application=new TextUI();
    DefCommand def(application);
    AddCommand add(application);
    def.execute("cSmall = Circle(2,1,1)");
    def.execute("rTall = Rectangle(1,10,2,8)");
    def.execute("comboExclamation = combo{rTall,cSmall}");
    def.execute("cMale = Circle(3,2,1)");
    add.execute("cMale to comboExclamation");
    auto it=application->mediaList.find("comboExclamation");
    DescriptionVisitor dv,dv2,dv3;
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv);
    }
    CHECK(string("combo(r(1 10 2 8) c(2 1 1) c(3 2 1) )") == dv.getDescription());

    add.undo();
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv2);
    }
    CHECK(string("combo(r(1 10 2 8) c(2 1 1) )") == dv2.getDescription());

    add.redo();
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv3);
    }
    CHECK(string("combo(r(1 10 2 8) c(2 1 1) c(3 2 1) )") == dv3.getDescription());
}

//5. delete
TEST(DelFromComboMedia, DeleteCommand)
{
    TextUI* application=new TextUI();
    DefCommand def(application);
    DeleteCommand del(application);
    def.execute("cSmall = Circle(2,1,1)");
    def.execute("rTall = Rectangle(1,10,2,8)");
    def.execute("comboExclamation = combo{rTall,cSmall}");
    del.execute("cSmall from comboExclamation");
    auto it=application->mediaList.find("comboExclamation");
    DescriptionVisitor dv,dv2,dv3;
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv);
    }
    CHECK(string("combo(r(1 10 2 8) )") == dv.getDescription());

    del.undo();
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv2);
    }

    CHECK(string("combo(r(1 10 2 8) c(2 1 1) )") == dv2.getDescription());

    del.redo();
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv3);
    }
    CHECK(string("combo(r(1 10 2 8) )") == dv3.getDescription());
}

TEST(DelShape, DeleteCommand)
{
    TextUI* application=new TextUI();
    DefCommand def(application);
    DeleteCommand del(application);
    def.execute("r = Rectangle(0,0,10,10)");
    del.execute("r");
    auto it=application->mediaList.find("r");
    if(it!=application->mediaList.end()) {
        FAIL("Should not be here");
    }
    CHECK(application->mediaList.empty() == true);

    del.undo();
    it=application->mediaList.find("r");
    DescriptionVisitor dv;
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv);
    }
    CHECK(string("r(0 0 10 10) ") == dv.getDescription());

    del.redo();
    it=application->mediaList.find("r");
    if(it!=application->mediaList.end()) {
        FAIL("Should not be here");
    }
    CHECK(application->mediaList.empty() == true);
}

TEST(DelCombo, DeleteCommand)
{
    TextUI* application=new TextUI();
    DefCommand def(application);
    DeleteCommand del(application);
    def.execute("cSmall = Circle(2,1,1)");
    def.execute("rTall = Rectangle(1,10,2,8)");
    def.execute("comboExclamation = combo{rTall,cSmall}");
    del.execute("comboExclamation");
    auto it=application->mediaList.find("comboExclamation");
    if(it!=application->mediaList.end()) {
        FAIL("Should not be here");
    }
    LONGS_EQUAL(application->mediaList.size(), 2);

    del.undo();
    DescriptionVisitor dv;
    it=application->mediaList.find("comboExclamation");
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv);
    }
    CHECK(string("combo(r(1 10 2 8) c(2 1 1) )") == dv.getDescription());
    LONGS_EQUAL(application->mediaList.size(), 3);

    del.redo();
    it=application->mediaList.find("comboExclamation");
    if(it!=application->mediaList.end()) {
        FAIL("Should not be here");
    }
    LONGS_EQUAL(application->mediaList.size(), 2);
}

//2. CommandManager
TEST(Def, CommandManager)
{
    TextUI* application=new TextUI();
    CommandManager cm(application);
    DescriptionVisitor dv,dv2,dv3,dv4;
    cm.commandToExecute("def cSmall = Circle(2,1,1)");
    auto it=application->mediaList.find("cSmall");
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv);
    }
    CHECK(string("c(2 1 1) ") == dv.getDescription());

    cm.commandToExecute("def rTall = Rectangle(1,10,2,8)");
    cm.commandToExecute("def comboExclamation = combo{rTall,cSmall}");
    it=application->mediaList.find("comboExclamation");
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv2);
    }
    CHECK(string("combo(r(1 10 2 8) c(2 1 1) )") == dv2.getDescription());
    LONGS_EQUAL(application->mediaList.size(), 3);

    cm.undoCommand();
    it=application->mediaList.find("comboExclamation");
    if(it!=application->mediaList.end()) {
        FAIL("Should not be here");
    }
    LONGS_EQUAL(application->mediaList.size(), 2);

    cm.undoCommand();
    it=application->mediaList.find("rTall");
    if(it!=application->mediaList.end()) {
        FAIL("Should not be here");
    }
    LONGS_EQUAL(application->mediaList.size(), 1);

    cm.redoCommand();
    it=application->mediaList.find("rTall");
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv3);
    }
    //cout <<dv.getDescription()<<endl;
    CHECK(string("r(1 10 2 8) ") == dv3.getDescription());

    cm.redoCommand();
    it=application->mediaList.find("comboExclamation");
    if(it!=application->mediaList.end()) {
        Media* m=it->second;
        m->accept(&dv4);
    }
    CHECK(string("combo(r(1 10 2 8) c(2 1 1) )") == dv4.getDescription());
}

#endif // UTSHAPES_H_INCLUDED
