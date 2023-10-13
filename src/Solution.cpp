#include "Solution.h"

Solution::Solution(Problem *data) {
    std::vector<std::vector<Node*>> trips;
    trips.resize(data->getTripsAmount(), std::vector<Node*>());
    _tripsLength.resize(data->getTripsLength().size());
    for(float length : data->getTripsLength()) {
        _tripsLength.push_back(length);
    }
    this->trips = trips;
}

Solution::~Solution() {
}

void Solution::calculateSolutionScore() {
    this->_value = 0.0;
    for(auto trip : this->trips) {
        for(auto node : trip) {
            this->_value += node->getScore();
        }
    }
}

double Solution::value() const{
    return this->_value;
}

std::vector<std::vector<Node*>> Solution::getTrips() const {
    return this->trips;
}

void Solution::print_solution() {
    this->calculateSolutionScore();
    std::cout << this->value() << std::endl;
}

Solution::Solution(const Solution* other) {
    // Copy the value
    this->_value = other->_value;

    // Copy the trips
    for (const auto& trip : other->trips) {
        std::vector<Node*> tripCopy;
        for (const auto& node : trip) {
            // Create a new Node using the Node copy constructor
            Node* newNode = new Node(node);
            tripCopy.push_back(newNode);
        }
        this->trips.push_back(tripCopy);
    }
}

std::ostream& operator<<(std::ostream& os, const Solution& solution) {
    os << "Solution value: " << solution.value() << "\n";
    os << "Trips:\n";

    for (const auto& trip : solution.getTrips()) {
        os << "  Trip:\n";
        for (const auto& node : trip) {
            os << "    Node (x: " << node->get_x() << ", y: " << node->get_y() << ", score: " << node->getScore() << ")\n";
        }
    }

    return os;
}