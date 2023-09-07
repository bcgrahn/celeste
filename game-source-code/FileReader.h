#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>

using namespace std;

class FileReader
{
public:
    FileReader();
    string getInfo();

private:
    string info;
};

#endif
