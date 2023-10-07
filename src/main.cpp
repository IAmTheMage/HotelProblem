#include "FileManager.h"
#include "Algorithm.h"

int main(int argc, char const *argv[])
{
    std::string _path(argv[1]);

    Problem* defs = FileManager::getFromFile(_path);
    std::cout << *defs << std::endl;

    std::cout << std::endl;

    Algorithm *alg = new Algorithm(defs);

    alg->constructive();

    alg->getSolution()->print_solution();

    return 0;
}
