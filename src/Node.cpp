#include "Node.h"

Node::Node(float x, float y, float score) {
    _x = x;
    _y = y;
    _score = score;
}

Node::~Node() {

}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "[ X: " << node._x << ", Y: " << node._y << " ";
    os << "Score: " << node._score << " ";
    os << "ST: " << node._st << ", OPT: " << node._opt << ", CLT: " << node._clt << " ]";

    return os;
}

Node::Node(const Node* other) {
    this->_x = other->_x;
    this->_y = other->_y;
    this->_score = other->_score;
    this->_st = other->_st;
    this->_opt = other->_opt;
    this->_clt = other->_clt;
    this->_actual_benefit = other->_actual_benefit;
    this->id = other->id;
}
