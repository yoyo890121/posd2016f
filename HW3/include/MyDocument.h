#ifndef MYDOCUMENT_H
#define MYDOCUMENT_H

#include "Document.h"
#include <string>
#include <fstream>
using namespace std;

class MyDocument : public Document
{
public:
    void openFile(const string name);
    bool canOpenDocument(const string name);
    string readFile();
private:
    fstream fs;
};

#endif // MYDOCUMENT_H
