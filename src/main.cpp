#include "FileManager.h"
#include "Algorithm.h"

int main(int argc, char const *argv[])
{
    //std::string _path(argv[1]);
    std::string _path = "/home/yan/HotelProblem/instances/SET1_1-2/64-45-1-2.ophs";

    Problem* defs = FileManager::getFromFile(_path);
    //std::cout << *defs << std::endl;

    //std::cout << std::endl;

    Algorithm *alg = new Algorithm(defs);

    alg->adaptativeRandomGreedy(200, 10, 200);

    alg->getSolution()->print_solution();

    return 0;
}
