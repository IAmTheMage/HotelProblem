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

        double localHeuristc(Node* actualNode, Node* b, double tripMaxTime);
        bool sortCandidateListBasedOnBenefit(Node* a, Node* b);

        std::vector<Node*> generateCandidateList(std::vector<Node*> trip, std::vector<Node*> hotels, std::vector<Node*> customers, int actual_trip);

        double calculateTimeBetweenNodes(Node* a, Node* b);

        Solution* initial_solution;
        Problem* data;
        std::vector<float> _tripsLength;
};

#endif