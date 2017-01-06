#include "DefCommand.h"
#include <sstream>
#include <iostream>

DefCommand::DefCommand(TextUI *textui):_textui(textui) {}

void DefCommand::execute(string cmd) {
    _cmd=cmd;

    stringstream ss(cmd);
    string name,check,type;
    ss >>name>>check;
    if (check!="=") {
        cout <<"command error!"<<endl; //throw exception
    }
    ss >>type;
    stringstream typess(type);
    getline(typess,type,'(');
    if (type=="Circle" || type=="Rectangle" || type=="Triangle") {
        string numbers;
        typess >>numbers;
        _textui->defShapeMedia(name, type, numbers);
    }
    size_t found = type.find("combo");
    if (found!=string::npos) {
        size_t begin_pos = type.find("{");
        size_t end_pos = type.find("}");
        string shapeString = type.substr (begin_pos+1,end_pos-begin_pos-1);
        _textui->defComboMedia(name, shapeString);
    }
}

void DefCommand::undo() {
    stringstream ss(_cmd);
    string name,check,type;
    ss >>name>>check;
    _textui->deleteMedia(name);
}

void DefCommand::redo() {
    this->execute(_cmd);
}
