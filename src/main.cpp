#include "FileManager.h"

int main(int argc, char const *argv[])
{
    std::string _path(argv[1]);

    Problem* defs = FileManager::getFromFile(_path);
    std::cout << *defs << std::endl;
    return 0;
}
