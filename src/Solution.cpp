#include "Solution.h"
#include <math.h>

Solution::Solution(Problem *data) {
    std::vector<std::vector<Node*>> trips;
    trips.resize(data->getTripsAmount(), std::vector<Node*>());
    this->trips = trips;
}

Solution::~Solution() {
    for(auto i : this->trips) {
        i.resize(0);
    }
    this->trips.resize(0);
}

void Solution::calculateSolutionScore() {
    this->_value = 0.0;
    for(auto trip : this->trips) {
        for(auto node : trip) {
            this->_value += node->getScore();
        }
    }
}

double Solution::value() {
    return this->_value;
}

std::vector<std::vector<Node*>> Solution::getTrips() {
    return this->trips;
}

void Solution::print_solution() {
    for(auto trip : this->trips) {
        for(auto i : trip) {
            std::cout << "Node: (" << i->get_x() << "," << i->get_y() << ") Score: " << i->getScore() << " id: " << i->getId() << std::endl;
        }
        std::cout << "-------------------------------------\n";
    }

    this->calculateSolutionScore();
    std::cout << "\nQualidade da solução: " << this->value() << std::endl;

    std::cout << "\n=======================================\n";
}