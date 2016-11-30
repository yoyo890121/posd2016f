#include "MediaDirector.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <sstream>
#include <iostream>

void MediaDirector::setMediaBuilder(std::stack<MediaBuilder *> *mbs) {
    int it;
    for (it = 0; it < result.size(); it++) {
        //cout << result[it] << endl;
        stringstream ss(result[it]);
        char c;
        //cout <<ss.str()<<endl;
        if (result[it]=="combo") {
            mbs->push(new ComboMediaBuilder());
            mbs->top()->buildComboMedia();
            continue;
        }
        else if(result[it]==")combo") {
            Media *cm2 = mbs->top()->getMedia(); //)
            if(mbs->size()!=1) {
                mbs->pop();
                mbs->top()->buildAddComboMedia(cm2);
                ss.get(c);
            }
            mbs->push(new ComboMediaBuilder());
            mbs->top()->buildComboMedia();
            continue;
        }
        else {
            ss.get(c);
            if (c==')') {
                //do pack comboMedia
                Media *cm2 = mbs->top()->getMedia(); //)
                if(mbs->size()!=1) {
                    mbs->pop();
                    mbs->top()->buildAddComboMedia(cm2);
                    ss.get(c);
                }
            }

            if (c=='r') {
                if(it==0) {
                    mbs->push(new ShapeMediaBuilder());
                }
                it++;
                stringstream sss(result[it]);
                double x, y, l ,w;
                sss >> x>>y>>l>>w;
                Rectangle *r=new Rectangle(x,y,l,w);
                mbs->top()->buildShapeMedia(r);
                continue;
            }
            if (c=='c') {
                if(it==0) {
                    mbs->push(new ShapeMediaBuilder());
                }
                it++;
                stringstream sss(result[it]);
                double x,y,r;
                sss >>x>>y>>r;
                Circle *c=new Circle(x,y,r);
                mbs->top()->buildShapeMedia(c);
                continue;
            }
            if (c=='t') {
                if(it==0) {
                    mbs->push(new ShapeMediaBuilder());
                }
                it++;
                stringstream sss(result[it]);
                double pAX,pAY,pBX,pBY,pCX,pCY;
                sss >>pAX>>pAY>>pBX>>pBY>>pCX>>pCY;
                Triangle *t=new Triangle(pAX,pAY,pBX,pBY,pCX,pCY);
                mbs->top()->buildShapeMedia(t);
                continue;
            }
        }
    }
}

void MediaDirector::concrete(std::string content) {
    stringstream ss1(content),ss2;
    string sub1,sub2;
    //cout <<ss1.str()<<endl;
    while (getline(ss1,sub1,'(')) {
        //std::cout << "sub1 is " <<sub1 << std::endl;
        ss2.clear();
        ss2 <<sub1;
        string delim(") ");
        size_t begin_pos=0, end_pos=sub1.find(delim);
        while(end_pos!=string::npos) {
            sub2=sub1.substr(begin_pos, end_pos-begin_pos);
            //std::cout << "sub2 is " <<sub2 << std::endl;
            result.push_back(sub2); // extract the sub-string before current delimiter
            begin_pos = end_pos+delim.size();
            end_pos = sub1.find(delim, begin_pos);  // locate the next delimiter in string
        }
        result.push_back(sub1.substr(begin_pos, end_pos-begin_pos));  // extract the last sub-string
    }

//    for (auto i:result) {
//        cout <<i<<endl;
//    }
}

