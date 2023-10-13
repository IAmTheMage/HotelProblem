#ifndef SOLUTION_H
#define SOLUTION_H

#include "Node.h"
#include "Problem.h"
#include <vector>
#include "cmath"
#include "iostream"



class Solution {
    public:
        Solution(Problem *data);
        Solution(const Solution* other);
        ~Solution();

        double value() const;

        std::vector<std::vector<Node*>> getTrips() const;

        void setSolutionInstance(std::vector<std::vector<Node*>> ins) {this->trips = ins;}

        void setSelectedPoint(int i, int j, Node* hC) {
            trips[i][j] = hC;
        }

        bool canSwap(int indexN1, int indexN2) {

        }

        double _calcTime(Node* a, Node* b) {
            return sqrt(pow(a->get_x() - b->get_x(), 2) + pow(a->get_y() - b->get_y(), 2));
        }

        void length() {
            for(int i = 0; i < trips.size(); i++) {
                double sum = (double)0.0;
                for(int j = 0; j < trips[i].size() - 1; j++) {
                    sum += _calcTime(trips[i][j], trips[i][j+1]);
                }

                std::cout << "Trip {" << i << "}" << " length => " << sum << std::endl;
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const Solution& solution);


        void print_solution();
    private:
        double _value;

        void calculateSolutionScore();

        std::vector<std::vector<Node*>> trips;
        std::vector<float> _tripsLength;
};

#endif