#include "CommandManager.h"
#include "AddCommand.h"
#include "DefCommand.h"
#include "DeleteCommand.h"

#include <sstream>
#include <iostream>

CommandManager::CommandManager(TextUI *textui):_textui(textui) {}

void CommandManager::commandToExecute(string input) {
        stringstream ss(input);
        string instruction;
        ss >>instruction;
        Command* cmd=nullptr;
        if (instruction=="def") {
            cmd = new DefCommand(_textui);
        }
        if (instruction=="add") {
            cmd = new AddCommand(_textui);
        }
        if (instruction=="delete") {
            cmd = new DeleteCommand(_textui);
        }
        if (cmd!=nullptr) {
            string subcmd=ss.str();
            size_t begin_pos = subcmd.find(" ");
            size_t end_pos = subcmd.size();
            subcmd = subcmd.substr (begin_pos+1,end_pos-begin_pos-1);
            this->executeCommand(cmd,subcmd);
            //cout <<"Command execute success"<<endl;
        } else {
            cout <<"Command input error"<<endl;
        }
}

void CommandManager::executeCommand(Command *cmd, string subcmd) {
    cmd->execute(subcmd);
    undocmds.push(cmd);
}

void CommandManager::redoCommand() {
    if(!redocmds.empty()) {
        redocmds.top()->redo();
        undocmds.push(redocmds.top());
        redocmds.pop();
    } else {
        cout <<"Can not redo"<<endl;
    }
}

void CommandManager::undoCommand() {
    if(!undocmds.empty()) {
        undocmds.top()->undo();
        redocmds.push(undocmds.top());
        undocmds.pop();
    } else {
        cout <<"Can not undo"<<endl;
    }
}
