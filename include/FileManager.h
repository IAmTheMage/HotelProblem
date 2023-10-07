#include "string"
#include "fstream"
#include <sstream>
#include <vector>
#include "iostream"

#include "Problem.h"


#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H


class FileManager {
    public:
        FileManager();
        ~FileManager();
        static Problem* getFromFile(std::string path);
};

#endif