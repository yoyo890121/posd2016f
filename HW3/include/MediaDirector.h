#ifndef MEDIADIRECTOR_H
#define MEDIADIRECTOR_H
#include <stack>
#include <string>
#include <vector>
#include "MediaBuilder.h"
#include "ComboMediaBuilder.h"
#include "ShapeMediaBuilder.h"
using namespace std;

class MediaDirector {
public :
    void setMediaBuilder(std::stack<MediaBuilder *> *mbs);
    void concrete(std::string content);
private :
    std::stack<MediaBuilder *> *mb;
    vector<string> result;
};


#endif // MEDIADIRECTOR_H
