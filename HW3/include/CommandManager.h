#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include "Command.h"
#include <stack>

using namespace std;

class CommandManager {
public:
    CommandManager(TextUI *textui);
    void commandToExecute(string input);
    void executeCommand(Command *cmd, string subcmd);
    void redoCommand();
    void undoCommand();
private:
    stack<Command*> undocmds;
    stack<Command*> redocmds;
    TextUI* _textui;
    //Command* cmd;
};

#endif // COMMANDMANAGER_H
