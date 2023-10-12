#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Problem.h"
#include "Solution.h"

class Algorithm {
    public:
        Algorithm(Problem *data);
        ~Algorithm();

        std::vector<std::vector<Node*>> randomGreedy(float alpha, int iter);
        void adaptativeRandomGreedy(int numIter, int block, int randomGreedyNumIter);

        Solution* getSolution() {return this->best_solution;}
    private:

        std::vector<std::vector<Node*>> randomGreedyIter(float alpha);

        void setAlphas(std::vector<float>& alphas);
        void initializeVectors(std::vector<double>& medians, std::vector<double>& prob, int size);
        void updateProbabilities(std::vector<double>& median, std::vector<double>& probabilities, std::vector<double>& bestSolutions, std::vector<double>& q);
        int selectProbabilitie(std::vector<double>& prob);
        void updateMedians(std::vector<double>& medians, double solution, std::vector<float> alphas,  std::vector<double> sums, float alpha, std::vector<int> solutionsAmount);

        double localHeuristc(Node* actualNode, Node* b, double tripMaxTime);
        static bool sortCandidateListBasedOnBenefit(Node* a, Node* b);

        std::vector<Node*> generateCandidateList(std::vector<Node*> trip, std::vector<Node*> hotels, std::vector<Node*> customers, int actual_trip);

        double calculateSolutionQuality(std::vector<std::vector<Node*>> solution);
        double calculateTimeBetweenNodes(Node* a, Node* b);

        void makeDistanceMatrix(int size);

        Solution* initial_solution;
        Solution* best_solution;
        Problem* data;
        std::vector<float> _tripsLength;
        std::vector<std::vector<double>> distance_matrix;
};

#endif