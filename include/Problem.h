#ifndef PROBLEM_H
#define PROBLEM_H

#include "map"
#include "string"
#include "Node.h"
#include "vector"
#include "iostream"

class Problem {
    public:
        Problem(int vertexAmount, int hotelsAmount, int tripsAmount, int totalTourLength);
        ~Problem();

        void addTripLength(float tripLength);


        friend std::ostream& operator<<(std::ostream& os, const Problem& problem);

        void setFirstHotel(float x, float y, float score);
        void setFinalHotel(float x, float y, float score);
        void addHotel(float x, float y, float score);
        void addCustomer(float x, float y, float score);
        
        int getTripsAmount() {return this->_tripsAmount;}
        std::vector<Node*> getHotels() {return this->hotels;}
        std::vector<Node*> getCustomers() {return this->customers;}
        std::vector<float> getTripsLength() {return this->_tripsLength;}

        void setNodeIds();
    private:
        int _vertexAmount;
        int _hotelsAmount;
        int _tripsAmount;
        int _totalTourLength;
        std::vector<float> _tripsLength;
        std::vector<Node*> hotels;
        std::vector<Node*> customers;
        int current_k;
};

#endif