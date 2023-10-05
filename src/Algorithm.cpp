#include "Algorithm.h"

Algorithm::Algorithm(Problem *data) {
    Solution* solution = new Solution(data);
    this->initial_solution = solution;
}

Algorithm::~Algorithm() {
    this->initial_solution->~Solution();
}

void Algorithm::constructive() {

}