#ifndef NODE_H
#define NODE_H
#include "iostream"

#include "string"

class Node {
    public:
        Node(float x, float y, float score, float st, float opt, float clt);
        ~Node();

        friend std::ostream& operator<<(std::ostream& os, const Node& node);
        
    private:
        float _x;
        float _y;
        float _score;
        float _st;
        float _opt;
        float _clt;
};

#endif