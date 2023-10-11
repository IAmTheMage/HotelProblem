#include "FileManager.h"
#include "Algorithm.h"

int main(int argc, char const *argv[])
{
    //std::string _path(argv[1]);

    std::string _path = "/home/yan/HotelProblem/instances/instances1/64-45-5-3.ophstw";

    Problem* defs = FileManager::getFromFile(_path);
    std::cout << *defs << std::endl;

    std::cout << std::endl;

    Algorithm *alg = new Algorithm(defs);

    alg->randomGreedy(0.05f,100);

    alg->getSolution()->print_solution();

    return 0;
}
