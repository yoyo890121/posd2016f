#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "Command.h"

class AddCommand : public Command {
public:
    AddCommand (TextUI* textui);
    void execute(string cmd);
    void undo();
    void redo();
private:
    TextUI* _textui;
};

#endif // ADDCOMMAND_H
