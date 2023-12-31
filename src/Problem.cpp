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
    os << "Problem definition" << std::endl;
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

    os << "Customers:" << std::endl;
    for (size_t i = 0; i < problem.customers.size(); ++i) {
        os << "  Node " << i + 1 << ": " << *problem.customers[i] << std::endl;
    }

    return os;
}

void Problem::setFirstHotel(float x, float y, float score) {
    Node* node = new Node(x, y, score);
    this->hotels[0] = node;
}

void Problem::setFinalHotel(float x, float y, float score) {
    Node* node = new Node(x, y, score);
    this->hotels[this->hotels.size() - 1] = node;
}

void Problem::addHotel(float x, float y, float score) {
    Node* node = new Node(x, y, score);
    this->hotels[this->current_k] = node;
    this->current_k++;
}

void Problem::addCustomer(float x, float y, float score) {
    Node* node = new Node(x, y, score);
    this->customers.push_back(node);
}

void Problem::setNodeIds() {
    int k;
    for(int i=0; i<this->hotels.size(); i++) {
        k = i;
        this->hotels[i]->setId(k);
    }
    for(int i=0; i<this->customers.size(); i++) {
        k++;
        this->customers[i]->setId(k);
    }
}