#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include "vector"
#include "Movement.h"
#include "iostream"
#include <random>

#define INITIAL_TEMPERATURE 100.f
#define COOLING_FACTOR 0.01
#define ME 0.05
#define ITERATIONS_PER_TEMPERATURE 100

enum class decay_type {
    LINEAR = 0, QUADRATIC = 1
};

class SimulatedAnnealing {
    public:
        SimulatedAnnealing(const std::vector<Movement*>& movements, float initial_temperature = INITIAL_TEMPERATURE,
        float cooling_factor = COOLING_FACTOR, float minimum_energy = ME, int iterations_per_temperature = ITERATIONS_PER_TEMPERATURE, 
        decay_type type = decay_type::LINEAR);
        Solution* run(const Solution* initialSolution, int verboseLevel = 10);
        Solution* runParallel(const Solution* initialSolution, int verboseLevel = 10);
        ~SimulatedAnnealing();

    private:
        decay_type _decay_type;
        float _initial_temperature;
        float _temperature;
        float _cooling_factor;
        float _minimum_energy;
        float _iterations_per_temperature;
        std::vector<Movement*> _movements;

};

#endif