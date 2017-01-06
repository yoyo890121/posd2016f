#ifndef DEFCOMMAND_H
#define DEFCOMMAND_H

#include "Command.h"


class DefCommand : public Command
{
public:
    DefCommand (TextUI* textui);
    void execute(string cmd);
    void undo();
    void redo();
private:
    TextUI* _textui;
};

#endif // DEFCOMMAND_H
