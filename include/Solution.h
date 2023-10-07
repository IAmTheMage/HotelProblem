#ifndef SOLUTION_H
#define SOLUTION_H

#include "Node.h"
#include "Problem.h"
#include <vector>

class Solution {
    public:
        Solution(Problem *data);
        ~Solution();

        double value();

        std::vector<std::vector<Node*>> getTrips();

        void setSolutionInstance(std::vector<std::vector<Node*>> ins) {this->trips = ins;}

        void print_solution();
    private:
        double _value;

        void calculateSolutionScore();

        std::vector<std::vector<Node*>> trips;
};

#endif