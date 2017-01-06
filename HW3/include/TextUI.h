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
    void start();
    void processCommand(string cmd);
    void defShapeMedia(string name, string type, string numbers);
    void defComboMedia(string name, string shapeString);
    void addMedia(string mediaName, string comboMediaName);
    void deleteMedia(string mediaName);
    void deleteFromComboMedia(string mediaName, string comboMediaName);
    map<string, Media*> mediaList;
private:
    string input;
};
vector<string> split(const string &source, const char &delim);
#endif // TEXTUI_H
