#ifndef SOLUTION_H
#define SOLUTION_H

#include "Node.h"
#include "Problem.h"
#include <vector>

class Solution {
    public:
        Solution(Problem *data);
        Solution(const Solution* other);
        ~Solution();

        double value() const;

        std::vector<std::vector<Node*>> getTrips() const;

        void setUnusedCustomers(const std::vector<Node*>& _unused) {
            for(const auto& unused : _unused) {
                this->unused_customers.push_back(unused);
            }
        }

        void setSolutionInstance(std::vector<std::vector<Node*>> ins) {this->trips = ins;}

        void print_solution();

        void calculateTripLength();

        void setSelectedPoint(int i, int j, Node* hC) {
            trips[i][j] = hC;
        }

        std::vector<Node*> getUnusedCostumers() {
            return this->unused_customers;
        }

        bool canSwap(int trip1, int trip2, int customer1, int customer2);
        bool canSwap(int trip, int customer, Node* unused);
        void swap(int trip1, int trip2, int customer1, int customer2);
        void swap(int trip, int customer, Node* unused);
        void insertIn(Node* n, int trip, int position) {
            this->trips[trip].insert(this->trips[trip].begin() + position, n);
        };
        float getAvaliableLengthIfRemoved(int trip, int customer);
        void calculateSolutionScore();
        float getInsertCost(Node* n1, int trip, int customer);

        void removeUnused(int index) {
            this->unused_customers.erase(this->unused_customers.begin() + index);
        } 

        void addUnused(Node* unused) {
            this->unused_customers.push_back(unused);
        }

        bool isValid();

        friend std::ostream& operator<<(std::ostream& os, const Solution& solution);
    private:
        double _value;

        

        std::vector<std::vector<Node*>> trips;
        std::vector<double> trips_length;
        std::vector<float> tripsMaxLength;
        std::vector<Node*> unused_customers;
};

#endif