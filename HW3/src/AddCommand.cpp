#include "AddCommand.h"
#include <sstream>

AddCommand::AddCommand(TextUI *textui):_textui(textui) {}

void AddCommand::execute(string cmd) {
    _cmd=cmd;
    stringstream ss(cmd);
    string mediaName,check,comboMediaName;
    ss >>mediaName>>check>>comboMediaName;
    _textui->addMedia(mediaName, comboMediaName);
}

void AddCommand::undo() {
    stringstream ss(_cmd);
    string mediaName,check,comboMediaName;
    ss >>mediaName>>check>>comboMediaName;
    _textui->deleteFromComboMedia(mediaName, comboMediaName);
}

void AddCommand::redo() {
    this->execute(_cmd);
}
