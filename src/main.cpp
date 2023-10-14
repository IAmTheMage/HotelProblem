#include "FileManager.h"
#include "Algorithm.h"
#include "SwapCustomers.h"
#include "InsertNewCustomer.h"
#include "SwapWithUnusedCustomers.h"
#include "SimulatedAnnealing.h"
#include "SwapHotels.h"
#include "SwapCustomersInTrip.h"

/*
(3, 0)
(-3, -4)
(5, 0)
*/

int main(int argc, char const *argv[])
{
    std::string _path(argv[1]);

    Problem* defs = FileManager::getFromFile(_path);
    std::cout << *defs << std::endl;

    //std::cout << std::endl;
    defs->setNodeIds();
    Algorithm *alg = new Algorithm(defs);

    int verbose = 100;

    alg->adaptativeRandomGreedy(500, 20, 100, verbose);

    Solution* sol = alg->getSolution();

    std::vector<Movement*> movements;
    movements.push_back(new SwapWithUnusedCostumers());
    movements.push_back(new SwapWithUnusedCostumers());
    movements.push_back(new SwapWithUnusedCostumers());
    movements.push_back(new SwapWithUnusedCostumers());
    movements.push_back(new SwapWithUnusedCostumers());
    movements.push_back(new SwapCustomers());
    movements.push_back(new InsertNewCustomer());
    movements.push_back(new InsertNewCustomer());
    movements.push_back(new InsertNewCustomer());
    movements.push_back(new InsertNewCustomer());
    movements.push_back(new InsertNewCustomer());
    movements.push_back(new SwapInTrip());
    

    SimulatedAnnealing* ann = new SimulatedAnnealing(movements);

    std::cout << *ann->run(sol, 80) << std::endl;


    return 0;
}
