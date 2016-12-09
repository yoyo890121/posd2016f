#include "..\cppunitlite\TestHarness.h"
#include "utShapes.h"
#include "TextUI.h"

int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);
    TextUI textUI;
    textUI.start();
    return 0;
}
