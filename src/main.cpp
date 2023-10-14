#include "FileManager.h"
#include "Algorithm.h"
#include "SwapCustomers.h"
#include "SwapWithUnusedCustomers.h"

/*
(3, 0)
(-3, -4)
(5, 0)
*/

int main(int argc, char const *argv[])
{
    std::string _path(argv[1]);

    Problem* defs = FileManager::getFromFile(_path);
    //std::cout << *defs << std::endl;

    //std::cout << std::endl;
    defs->setNodeIds();
    Algorithm *alg = new Algorithm(defs);

    int verbose = 100;

    alg->adaptativeRandomGreedy(500, 20, 100, verbose);

    Solution* sol = alg->getSolution();

    std::cout << sol->canSwap(1, 1, 4, 5) << std::endl;
    
    SwapWithUnusedCostumers* suc = new SwapWithUnusedCostumers();

    suc->exec(sol);

    return 0;
}
