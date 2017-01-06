#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "Command.h"

class DeleteCommand : public Command {
public:
    DeleteCommand(TextUI* textui);
    void execute(string cmd);
    void undo();
    void redo();
private:
    TextUI* _textui;
    Media* _deleteMedia;
    string _deleteMediaName;
};

#endif // DELETECOMMAND_H
