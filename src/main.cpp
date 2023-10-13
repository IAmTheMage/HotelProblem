#include "FileManager.h"
#include "Algorithm.h"
#include "SwapHotels.h"
#include "SwapCustomers.h"

int main(int argc, char const *argv[])
{
    std::string _path(argv[1]);

    Problem* defs = FileManager::getFromFile(_path);
    //std::cout << *defs << std::endl;

    //std::cout << std::endl;

    Algorithm *alg = new Algorithm(defs);

    alg->adaptativeRandomGreedy(200, 10, 10, 2);

    Solution* sol = alg->getSolution();
    sol->length();

    // SwapCustomers* custm = new SwapCustomers();

    // custm->exec(sol);
    
    return 0;
}
