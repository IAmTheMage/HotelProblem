#include "Solution.h"

Solution::Solution(Problem *data) {
    std::vector<std::vector<Node*>> trips;
    trips.reserve(data->getTripsAmount());
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