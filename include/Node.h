#ifndef NODE_H
#define NODE_H
#include "iostream"

#include "string"

class Node {
    public:
        Node(float x, float y, float score);
        ~Node();

        friend std::ostream& operator<<(std::ostream& os, const Node& node);

        float getScore() {return this->_score;}

        float get_x() {return this->_x;}
        float get_y() {return this->_y;}

        void setActualBenefit(double benefit) {this->_actual_benefit = benefit;}
        double getBenefit() {return this->_actual_benefit;}
    private:
        float _x;
        float _y;
        float _score;
        float _st;
        float _opt;
        float _clt;

        double _actual_benefit;
};

#endif