#ifndef TEXTUI_H
#define TEXTUI_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Media.h"
using namespace std;

class TextUI {
public:
    TextUI();
    void processCommand(string cmd);
    map<string, Media*> mediaList;
private:
    string input;
    void defShapeMedia(string name, string type, string numbers);
    void defComboMedia(string name, string shapeString);
};
vector<string> split(const string &source, const char &delim);
#endif // TEXTUI_H
