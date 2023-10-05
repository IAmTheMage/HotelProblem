#include "Algorithm.h"

Algorithm::Algorithm(Problem *data) {
    this->data = data; // dados do problema

    Solution* solution = new Solution(data);
    this->initial_solution = solution; // solução inicial vazia
}

Algorithm::~Algorithm() {
    this->initial_solution->~Solution();
}

void Algorithm::constructive() {
    std::vector<std::vector<Node*>> solution = this->initial_solution->getTrips();

    std::vector<Node*> hotels = this->data->getHotels();
    std::vector<Node*> customers = this->data->getCustomers();

    // hotel H0 inserido na primeira trip
    solution[0].push_back(hotels[0]);
}