#include "Node.h"

Node::Node(float x, float y, float score, float st, float opt, float clt) {
    _x = x;
    _y = y;
    _score = score;
    _st = st;
    _opt = opt;
    _clt = clt;
}

Node::~Node() {

}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "[ X: " << node._x << ", Y: " << node._y << " ";
    os << "Score: " << node._score << " ";
    os << "ST: " << node._st << ", OPT: " << node._opt << ", CLT: " << node._clt << " ]";

    return os;
}