#include "MyDocument.h"

void MyDocument::openFile(const string name) {
    fs.open(name);
}

bool MyDocument::canOpenDocument(const string name) {
    fs.open(name);
    bool canOpen=fs;
    fs.close();
    return canOpen;
}

string MyDocument::readFile() {
    string fileString;
    getline (fs,fileString);
    return fileString;
    fs.close();
}
