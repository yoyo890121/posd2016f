#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "TextUI.h"
using namespace std;

class Command {
public:
    virtual void execute(string cmd) = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
protected:
    string _cmd;
};

#endif // COMMAND_H
