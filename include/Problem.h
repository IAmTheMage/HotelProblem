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

        void setFirstHotel(float x, float y, float score, float st, float opt, float clt);
        void setFinalHotel(float x, float y, float score, float st, float opt, float clt);
        void addHotel(float x, float y, float score, float st, float opt, float clt);
        void addCustomer(float x, float y, float score, float st, float opt, float clt);
        
        int getTripsAmount() {return this->_tripsAmount;}
        std::vector<Node*> getHotels() {return this->hotels;}
        std::vector<Node*> getCustomers() {return this->customers;}
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