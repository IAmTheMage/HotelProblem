#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(const std::vector<Movement*>& movements, float initial_temperature,
        float cooling_factor, float minimum_energy, int iterations_per_temperature, 
        decay_type type) {
    
    this->_decay_type = type;
    this->_initial_temperature = initial_temperature;
    this->_cooling_factor = cooling_factor;
    this->_minimum_energy = minimum_energy;
    this->_iterations_per_temperature = iterations_per_temperature;
    this->_temperature = initial_temperature;
    for(Movement* mov : movements) {
        this->_movements.push_back(mov);
    }
}

Solution* SimulatedAnnealing::run(const Solution* initialSolution, int verboseLevel) {
    Solution* currentSolution = new Solution(initialSolution);
    currentSolution->calculateSolutionScore();

    Solution* bestSolution = new Solution(initialSolution);

    float originalQuality = currentSolution->value();

    std::cout << "Executing Simulated Annealing" << std::endl;
    while(this->_temperature > this->_minimum_energy) {
        for(int i = 0; i < this->_iterations_per_temperature; i++) {
            if(i % verboseLevel == 0) {
                std::cout << "Original quality: " << originalQuality << std::endl;
                std::cout << "Best solution fitness: " << currentSolution->value() << std::endl;
            }
            for(Movement* mov : this->_movements) {
                mov->setSeed(i + mov->getMemoryUsageInKB());
            }
            srand(time(NULL) + i + this->_movements[0]->getMemoryUsageInKB());
            int randomMovement = rand() % this->_movements.size();
            Solution* crt = this->_movements[randomMovement]->exec(currentSolution);

            

            double metropolisCriterion = std::exp((currentSolution->value() / crt->value()) / this->_temperature);
            double acepptance = ((double) rand() / RAND_MAX);
            
            if (crt->value() > currentSolution->value() || metropolisCriterion > acepptance) {
                currentSolution = new Solution(crt);
            }

            // update best solution if necessary
            if (currentSolution->value() > bestSolution->value()) {
                bestSolution = new Solution(currentSolution);
            }
        }

        this->_temperature *= (1 - this->_cooling_factor);
    }
    
    return bestSolution;
}

SimulatedAnnealing::~SimulatedAnnealing() {

}