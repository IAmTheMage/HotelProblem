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

    this->calculateTripLength();

    for(auto i : this->trips_length) {
        std::cout << i << "\n";
    }

    std::cout << "\n=======================================\n";
}


void Solution::calculateTripLength() {
    std::vector<double> aux;
    double sum = (double)0.0;
    Node* a;
    Node* b;
    for(auto trip : this->trips) {
        for(int j=0; j<trip.size()-1; j++) {
            a = trip[j];
            b = trip[j+1];
            sum = sum + sqrt(pow(a->get_x() - b->get_x(),2) + pow(a->get_y() - b->get_y(),2));
        }
        aux.push_back(sum);
        sum = (double)0.0;
    }

    std::cout << aux.size() << "\n";

    this->trips_length = aux;
}