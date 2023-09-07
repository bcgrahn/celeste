#include <iostream>
#include <fstream>
#include <string>
#include "FileReader.h"

using namespace std;

FileReader::FileReader()
{
    fstream newfile;
    string line = "";

    newfile.open("Resources/HowToPlay.txt", ios::in); // open a file to perform read operation using file object
    if (newfile.is_open())
    {
        while (getline(newfile, line))
        { // read data from file object and put it into string.
            info = info + line + "\n";
        }
        newfile.close();
    }
    else
    {
        info = "Cannot open file";
    }
}
string FileReader::getInfo()
{
    return info;
}
