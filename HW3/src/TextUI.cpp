#include "TextUI.h"
#include "MediaDirector.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "ComboMedia.h"
#include "MediaBuilder.h"
#include "ComboMediaBuilder.h"
#include "ShapeMediaBuilder.h"
#include "DescriptionVisitor.h"
#include <sstream>
#include <fstream>

TextUI::TextUI() {}

void TextUI::start() {
        while (cout <<":- ") {
        getline(cin,input);
        processCommand(input);
    }
}

void TextUI::processCommand(string cmd) {
    //cout <<cmd<<endl;
    stringstream ss(cmd);
    string instruction;
    ss >>instruction;
    //cout <<"instruction:"<<instruction<<endl;
    if (instruction=="def") {
        string name,check,type;
        ss >>name>>check;
        if (check!="=") {
            cout <<"command error!"<<endl; //throw exception
        }
        ss >>type;
        stringstream typess(type);
        getline(typess,type,'(');
        //cout <<"type:"<<type<<endl;
        if (type=="Circle" || type=="Rectangle" || type=="Triangle") {
            string numbers;
            typess >>numbers;
            //cout <<numbers<<endl;
            defShapeMedia(name, type, numbers);
        }
        size_t found = type.find("combo");
        if (found!=string::npos) {
            size_t begin_pos = type.find("{");
            size_t end_pos = type.find("}");
            string shapeString = type.substr (begin_pos+1,end_pos-begin_pos-1);
            defComboMedia(name, shapeString);
        }
    }
    if (instruction=="save") {
        string mediaName,check,fileName;
        ss >>mediaName>>check>>fileName;
        auto it=mediaList.find(mediaName);
        if (it!=mediaList.end() && check=="to") {
            fileName.erase(fileName.begin());
            fileName.pop_back();
            ofstream fout(fileName);
            if(!fout) {
                cout << "can not save file"<<endl;
            } else {
                Media* combo=it->second;
                DescriptionVisitor dv;
                combo->accept(&dv);
                fout <<dv.getDescription()<<endl;
                fout <<it->first<<"{";
                //use Media* to get mediaName
                vector<Media*> media=combo->getMedia();
                for (auto it:media) {
                    for (auto mediaListIt:mediaList) {
                        if (mediaListIt.second==it) {
                            fout<<mediaListIt.first<<" ";
                        }
                    }
                }
                fout <<"}"<<endl;
                fout.close();
                cout <<">> "<<mediaName<<" saved to "<<fileName<<endl;
            }
        } else {
            cout <<"command error!"<<endl;
        }
    }
    if (instruction=="show") {
        for (auto it:mediaList) {
            cout <<it.first<<endl;
        }
    }
    if (instruction=="add") {
        string mediaName,check,comboMediaName;
        ss >>mediaName>>check>>comboMediaName;
        auto comboMediaIt=mediaList.find(comboMediaName);
        auto mediaIt=mediaList.find(mediaName);
        if (comboMediaIt!=mediaList.end() && mediaIt!=mediaList.end()) {
            Media* combo=comboMediaIt->second;
            combo->add(mediaIt->second);
            DescriptionVisitor dv;
            combo->accept(&dv);
            //use Media* to get mediaName
            cout <<">> "<<comboMediaName<<" = "<<comboMediaName<<"{";
            vector<Media*> media=combo->getMedia();
            for (auto it:media) {
                for (auto mediaListIt:mediaList) {
                    if (mediaListIt.second==it) {
                        cout<<mediaListIt.first<<" ";
                    }
                }
            }
            cout <<"}= "<<dv.getDescription()<<endl;
        }
        else {
            cout <<"name not found"<<endl;
        }
    }
    if (instruction=="delete") {
        string mediaName,check,comboMediaName;
        ss >>mediaName>>check>>comboMediaName;
        auto mediaIt=mediaList.find(mediaName);
        if (mediaIt!=mediaList.end()) {
            if (check=="from") {
                auto comboMediaIt=mediaList.find(comboMediaName);
                if (comboMediaIt!=mediaList.end()) {
                    Media* combo=comboMediaIt->second;
                    combo->removeMedia(mediaIt->second);
                } else {
                    cout <<"name not found"<<endl;
                }
            } else {
                mediaList.erase(mediaIt);
            }
        } else {
            cout <<"name not found"<<endl;
        }
    }
    size_t areaFound = instruction.find(".area?");
    size_t perimeterFound = instruction.find(".perimeter?");
    if (areaFound!=string::npos || perimeterFound!=string::npos) {
        stringstream sss(instruction);
        string name;
        getline(sss,name,'.');
        auto it=mediaList.find(name);
        if (it != mediaList.end()) {
            //cout <<name<<endl;
            string type;
            getline(sss,type,'?');
            Media *m=it->second;
            if (type=="area") {
                cout <<">> "<<m->area()<<endl;
            }
            if (type=="perimeter") {
                cout <<">> "<<m->perimeter()<<endl;
            }
        } else {
            cout <<"name not found"<<endl;
        }
    }
}

void TextUI::defShapeMedia(string name, string type, string numbers) {
    vector<string> parameter=split(numbers,',');
    stringstream parameterss;
    for (auto it:parameter) {
        parameterss <<it<<" ";
    }
    ShapeMediaBuilder smb;
    if (type=="Circle") {
        double x,y,r;
        parameterss >>x>>y>>r;
        Circle* c=new Circle(x,y,r);
        smb.buildShapeMedia(c);
    }
    if (type=="Rectangle") {
        double x,y,l,w;
        parameterss >>x>>y>>l>>w;
        Rectangle* r=new Rectangle(x,y,l,w);
        smb.buildShapeMedia(r);
    }
    if (type=="Triangle") {
        double pAX,pAY,pBX,pBY,pCX,pCY;
        parameterss >>pAX>>pAY>>pBX>>pBY>>pCX>>pCY;
        try {
            Triangle* tri=new Triangle(pAX,pAY,pBX,pBY,pCX,pCY);
            smb.buildShapeMedia(tri);
        } catch(std::string s) {
            cout <<s<<endl;
        }
    }
    Media *m=smb.getMedia();
    mediaList.insert(pair<string, Media*>(name, m));
    auto it=mediaList.find(name);
    if (it != mediaList.end()) {
        cout <<">> "<<type<<" ("<<numbers<<endl;
    }
}

void TextUI::defComboMedia(string name, string shapeString) {
    vector<string> shapes=split(shapeString,',');
    bool isIllegalAdd=false;
    std::vector<Media *> ss;
    ComboMedia* combo=new ComboMedia(ss);
    for (auto shapesit:shapes) {
        //cout <<shapesit<<endl;
        auto mediasit=mediaList.find(shapesit);
        if (mediasit == mediaList.end()) {
            cout<<"shape not found:"<<shapesit<<endl;
            isIllegalAdd=true;
        } else {
            combo->add(mediasit->second);
        }
    }
    if (!isIllegalAdd) {
        mediaList.insert(pair<string, Media*>(name, combo));
    }
    auto it=mediaList.find(name);
    if (it != mediaList.end()) {
        cout <<">> Combo "<<name<<endl;
    }
    else {
        cout <<"Add combo fail"<<endl;
    }
}

vector<string> split(const string &source, const char &delim) {
    stringstream ss(source);
    string token;
    vector<string> ans;
    while (getline(ss, token, delim))
        ans.push_back(token);
    return ans;
}
