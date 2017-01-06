#include "..\cppunitlite\TestHarness.h"
#include "utShapes.h"
#include "TextUI.h"
#include "CommandManager.h"

int main()
{
    cout <<"Test mode"<<endl;
    TestResult tr;
    TestRegistry::runAllTests(tr);
    cout <<"Program mode"<<endl;
    TextUI* application=new TextUI();
    CommandManager cm(application);
    string input;
    while (cout <<":- ") {
        getline(cin,input);
        if (cin.eof()) {
            cm.undoCommand();
            cin.clear();
            continue;
        }
        if (int(input.at(0)==25)) {
            cm.redoCommand();
            continue;
        }
        cm.commandToExecute(input);
    }
    return 0;
}
