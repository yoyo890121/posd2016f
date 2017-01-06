#include "DeleteCommand.h"
#include <sstream>

DeleteCommand::DeleteCommand(TextUI *textui):_textui(textui) {}

void DeleteCommand::execute(string cmd) {
    _cmd=cmd;
    stringstream ss(cmd);
    string mediaName,check,comboMediaName;
    ss >>mediaName>>check>>comboMediaName;
    auto mediaIt=_textui->mediaList.find(mediaName);
    if (mediaIt!=_textui->mediaList.end()) {
        if (check=="from") {
            _textui->deleteFromComboMedia(mediaName, comboMediaName);
        } else {
            auto mediaIt=_textui->mediaList.find(mediaName);
            _deleteMedia=mediaIt->second;
            _deleteMediaName=mediaName;
            _textui->deleteMedia(mediaName);
        }
    } else {
        cout <<"name not found"<<endl;
    }
}

void DeleteCommand::undo() {
    stringstream ss(_cmd);
    string mediaName,check,comboMediaName;
    ss >>mediaName>>check>>comboMediaName;
    auto mediaIt=_textui->mediaList.find(mediaName);
    if (mediaIt!=_textui->mediaList.end()) {
        if (check=="from") {
            _textui->addMedia(mediaName, comboMediaName);
        }
    } else {
        _textui->mediaList.insert(pair<string, Media*>(_deleteMediaName, _deleteMedia));
    }
}

void DeleteCommand::redo() {
    this->execute(_cmd);
}
