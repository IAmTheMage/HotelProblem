#include "Problem.h" 

Problem::Problem(int vertexAmount, int hotelsAmount, int tripsAmount, int totalTourLength) {
    _vertexAmount = vertexAmount;
    _hotelsAmount = hotelsAmount;
    _tripsAmount = tripsAmount;
    _totalTourLength = totalTourLength;
    this->_tripsLength.reserve(tripsAmount);
    this->hotels.reserve(hotelsAmount + 2);
    this->hotels.resize(hotelsAmount + 2);
    this->current_k = 1;
}

Problem::~Problem() {
    
}

void Problem::addTripLength(float tripLength) {
    this->_tripsLength.push_back(tripLength);
}

std::ostream& operator<<(std::ostream& os, const Problem& problem) {
    os << "Vertex Amount: " << problem._vertexAmount << std::endl;
    os << "Hotels Amount: " << problem._hotelsAmount << std::endl;
    os << "Trips Amount: " << problem._tripsAmount << std::endl;
    os << "Total Tour Length: " << problem._totalTourLength << std::endl;

    os << "Trip Lengths:" << std::endl;
    for (size_t i = 0; i < problem._tripsLength.size(); ++i) {
        os << "  Trip " << i + 1 << ": " << problem._tripsLength[i] << std::endl;
    }

    os << "Hotels:" << std::endl;
    for (size_t i = 0; i < problem.hotels.size(); ++i) {
        os << "  Node " << i + 1 << ": " << *problem.hotels[i] << std::endl;
    }

    return os;
}

void Problem::setFirstHotel(float x, float y, float score, float st, float opt, float clt) {
    Node* node = new Node(x, y, score, st, opt, clt);
    this->hotels[0] = node;
}

void Problem::setFinalHotel(float x, float y, float score, float st, float opt, float clt) {
    Node* node = new Node(x, y, score, st, opt, clt);
    this->hotels[this->hotels.size() - 1] = node;
}

void Problem::addHotel(float x, float y, float score, float st, float opt, float clt) {
    Node* node = new Node(x, y, score, st, opt, clt);
    this->hotels[this->current_k] = node;
    this->current_k++;
}