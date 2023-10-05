#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Problem.h"
#include "Solution.h"

class Algorithm {
    public:
        Algorithm(Problem *data);
        ~Algorithm();
    
    private:
        void constructive();

        double calculateTimeBetweenNodes(Node* a, Node* b);

        Solution* initial_solution;
        Problem* data;
};

#endif