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
    private:
        double _value;

        void calculateSolutionScore();

        std::vector<std::vector<Node*>> trips;
};

#endif