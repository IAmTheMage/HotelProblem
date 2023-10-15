#include "Solution.h"
#include <math.h>
#include <unordered_set>

Solution::Solution(Problem *data) {
    std::vector<std::vector<Node*>> trips;
    trips.resize(data->getTripsAmount(), std::vector<Node*>());
    this->trips = trips;
    for(float length : data->getTripsLength()) {
        this->tripsMaxLength.push_back(length);
    }
}

Solution::~Solution() {
    for(auto i : this->trips) {
        i.resize(0);
    }
    this->trips.resize(0);
}

Solution::Solution(const Solution* other) {
    // Copy the value
    this->_value = other->_value;

    // Copy the trips
    for (const auto& trip : other->trips) {
        std::vector<Node*> tripCopy;
        for (const auto& node : trip) {
            // Create a new Node using the Node copy constructor
            Node* newNode = new Node(node);
            tripCopy.push_back(newNode);
        }
        this->trips.push_back(tripCopy);
    }

    for(float length : other->trips_length) {
        this->trips_length.push_back(length);
    }

    for(float maxLength : other->tripsMaxLength) {
        this->tripsMaxLength.push_back(maxLength);
    }

    for(Node* unused : other->unused_customers) {
        this->unused_customers.push_back(unused);
    }

    this->calculateSolutionScore();
    this->calculateTripLength();
}

bool Solution::isValid() {
    this->calculateTripLength();
    std::vector<double> trips_l = this->trips_length;
    for(int i=0; i< trips_l.size(); i++) {
        if(trips_l[i]>this->tripsMaxLength[i]) {
            std::cout << "[ERROR] trip " << i << "Maior que o comprimento permitido\n";
            return false;
        }
    }

    for(int i=0; i<this->trips.size()-1; i++) {
        if(trips[i].end() != trips[i+1].begin()) {
            std::cout << "[ERROR] Hotel do final da trip " << i << " diferente do hotel do início da próxima trip\n";
            return false;
        }
    }

    std::unordered_set<int> uniqueElements;

    for(auto trip : this->trips)
    {
        for (auto no : trip) {
            if (uniqueElements.count(no->getId()) > 0) {
                std::cout << "[ERROR] id repetido \n";
                return false;
            }
            uniqueElements.insert(no->getId());
        }
    }

    return true;
}

void Solution::calculateSolutionScore() {
    this->_value = 0.0;
    for(auto trip : this->trips) {
        for(auto node : trip) {
            this->_value += node->getScore();
        }
    }
    this->_value;
}

double Solution::value() const {
    return this->_value;
}

std::vector<std::vector<Node*>> Solution::getTrips() const {
    return this->trips;
}

void Solution::print_solution() {
    for(auto trip : this->trips) {
        for(auto i : trip) {
            std::cout << "Node: (" << i->get_x() << "," << i->get_y() << ") Score: " << i->getScore() << " id: " << i->getId() << std::endl;
        }
        std::cout << "-------------------------------------\n";
    }

    this->calculateSolutionScore();
    std::cout << "\nQualidade da solução: " << this->value() << std::endl;

    this->calculateTripLength();

    for(auto i : this->trips_length) {
        std::cout << i << "\n";
    }

    std::cout << "\n=======================================\n";
}


void Solution::calculateTripLength() {
    std::vector<double> aux;
    double sum = (double)0.0;
    Node* a;
    Node* b;
    for(auto trip : this->trips) {
        for(int j=0; j<trip.size()-1; j++) {
            a = trip[j];
            b = trip[j+1];
            sum = sum + sqrt(pow(a->get_x() - b->get_x(),2) + pow(a->get_y() - b->get_y(),2));
        }
        aux.push_back(sum);
        sum = (double)0.0;
    }

    this->trips_length = aux;
}

std::ostream& operator<<(std::ostream& os, const Solution& solution) {
    os << "Solution value: " << solution.value() << "\n";
    os << "Trips:\n";

    for (const auto& trip : solution.getTrips()) {
        os << "  Trip:\n";
        for (const auto& node : trip) {
            os << "    Node (x: " << node->get_x() << ", y: " << node->get_y() << ", score: " << node->getScore() << ")\n";
        }
    }

    return os;
}

bool Solution::canSwap(int _trip1, int _trip2, int customer1, int customer2) {
    this->calculateTripLength();
    double firstRemoveValue = (double)0.0, secondRemoveValue = (double)0.0, firstAddValue = (double)0.0, secondAddValue = (double)0.0;
    std::vector<Node*> trip1 = this->trips[_trip1];
    std::vector<Node*> trip2 = this->trips[_trip2];
    Node* firstCustomer = trip1[customer1];
    Node* secondCustomer = trip2[customer2];

    if(_trip1 > 0) {
        Node* afterFirstCustomer = trip1[customer1 + 1];
        firstRemoveValue += sqrt(pow(firstCustomer->get_x() - afterFirstCustomer->get_x(),2) + pow(firstCustomer->get_y() - afterFirstCustomer->get_y(),2));
        secondAddValue += sqrt(pow(secondCustomer->get_x() - afterFirstCustomer->get_x(),2) + pow(secondCustomer->get_y() - afterFirstCustomer->get_y(),2));
        //std::cout << "1 -> sqrt(pow(" << secondCustomer->get_x() << " - " << afterFirstCustomer->get_x() << ", 2) + pow(" << secondCustomer->get_y() << " - " << afterFirstCustomer->get_y() << ", 2))" << std::endl;
        //std::cout << "1.1 -> sqrt(pow(" << firstCustomer->get_x() << " - " << afterFirstCustomer->get_x() << ", 2) + pow(" << firstCustomer->get_y() << " - " << afterFirstCustomer->get_y() << ", 2))" << std::endl;
    }
    else if(_trip1 < trip1.size() - 1) {
        Node* beforeFirstCustomer = trip1[customer1 - 1];
        firstRemoveValue += sqrt(pow(firstCustomer->get_x() - beforeFirstCustomer->get_x(),2) + pow(firstCustomer->get_y() - beforeFirstCustomer->get_y(),2));
        secondAddValue += sqrt(pow(secondCustomer->get_x() - beforeFirstCustomer->get_x(),2) + pow(secondCustomer->get_y() - beforeFirstCustomer->get_y(),2));
        //std::cout << "2 -> sqrt(pow(" << secondCustomer->get_x() << " - " << beforeFirstCustomer->get_x() << ", 2) + pow(" << secondCustomer->get_y() << " - " << beforeFirstCustomer->get_y() << ", 2))" << std::endl;
        //std::cout << "2.1 -> sqrt(pow(" << firstCustomer->get_x() << " - " << beforeFirstCustomer->get_x() << ", 2) + pow(" << firstCustomer->get_y() << " - " << beforeFirstCustomer->get_y() << ", 2))" << std::endl;
    }

    if(_trip2 > 0) {
        Node* afterSecondCustomer = trip2[customer2 + 1];
        secondRemoveValue += sqrt(pow(secondCustomer->get_x() - afterSecondCustomer->get_x(),2) + pow(secondCustomer->get_y() - afterSecondCustomer->get_y(),2));
        firstAddValue += sqrt(pow(firstCustomer->get_x() - afterSecondCustomer->get_x(),2) + pow(firstCustomer->get_y() - afterSecondCustomer->get_y(),2));
        //std::cout << "3 -> sqrt(pow(" << firstCustomer->get_x() << " - " << afterSecondCustomer->get_x() << ", 2) + pow(" << firstCustomer->get_y() << " - " << afterSecondCustomer->get_y() << ", 2))" << std::endl;
        //std::cout << "3.1 -> sqrt(pow(" << secondCustomer->get_x() << " - " << afterSecondCustomer->get_x() << ", 2) + pow(" << secondCustomer->get_y() << " - " << afterSecondCustomer->get_y() << ", 2))" << std::endl;
    }
    else if(_trip2 < trip2.size() - 1) {
        Node* beforeSecondCustomer = trip2[customer2 - 1];
        secondRemoveValue += sqrt(pow(secondCustomer->get_x() - beforeSecondCustomer->get_x(),2) + pow(secondCustomer->get_y() - beforeSecondCustomer->get_y(),2));
        firstAddValue += sqrt(pow(firstCustomer->get_x() - beforeSecondCustomer->get_x(),2) + pow(firstCustomer->get_y() - beforeSecondCustomer->get_y(),2));
        //std::cout << "4 -> sqrt(pow(" << firstCustomer->get_x() << " - " << beforeSecondCustomer->get_x() << ", 2) + pow(" << firstCustomer->get_y() << " - " << beforeSecondCustomer->get_y() << ", 2))" << std::endl;
        //std::cout << "3.1 -> sqrt(pow(" << secondCustomer->get_x() << " - " << beforeSecondCustomer->get_x() << ", 2) + pow(" << secondCustomer->get_y() << " - " << beforeSecondCustomer->get_y() << ", 2))" << std::endl;
    }

    // std::cout << "Values:" << std::endl;
    // std::cout << "  Length 1-> " << this->trips_length[_trip1] << std::endl;
    // std::cout << "  Length 2-> " << this->trips_length[_trip2] << std::endl;
    // std::cout << "  firstRemoveValue-> " << firstRemoveValue << std::endl;
    // std::cout << "  secondRemoveValue-> " << secondRemoveValue << std::endl;
    // std::cout << "  firstAddValue-> " << firstAddValue << std::endl;
    // std::cout << "  secondAddValue-> " << secondAddValue << std::endl;
    // std::cout << "  MaxLength 1-> " << this->tripsMaxLength[_trip1] << std::endl;
    // std::cout << "  MaxLength 2-> " << this->tripsMaxLength[_trip2] << std::endl;

    float firstCanSwap = this->tripsMaxLength[_trip1] - (this->trips_length[_trip1] - firstRemoveValue + secondAddValue);
    float secondCanSwap = this->tripsMaxLength[_trip2] - (this->trips_length[_trip2] - secondRemoveValue + firstAddValue);
    return firstCanSwap > 0 && secondCanSwap > 0;
}

void Solution::swap(int trip1, int trip2, int customer1, int customer2) {
    Node* n1 = this->trips[trip1][customer1];
    Node* n2 = this->trips[trip2][customer2];

    this->trips[trip1][customer1] = n1;
    this->trips[trip2][customer2] = n2;
}

bool Solution::canSwap(int trip, int customer, Node* unused) {
    this->calculateTripLength();
    double firstRemoveValue = (double)0.0, toAddValue = (double)0.0;
    std::vector<Node*> trip1 = this->trips[trip];
    Node* firstCustomer = trip1[customer];

    if(trip > 0) {
        Node* afterFirstCustomer = trip1[customer + 1];
        firstRemoveValue += sqrt(pow(firstCustomer->get_x() - afterFirstCustomer->get_x(),2) + pow(firstCustomer->get_y() - afterFirstCustomer->get_y(),2));
        toAddValue += sqrt(pow(unused->get_x() - afterFirstCustomer->get_x(),2) + pow(unused->get_y() - afterFirstCustomer->get_y(),2));
        //std::cout << "1 -> sqrt(pow(" << unused->get_x() << " - " << afterFirstCustomer->get_x() << ", 2) + pow(" << unused->get_y() << " - " << afterFirstCustomer->get_y() << ", 2))" << std::endl;
        //std::cout << "1.1 -> sqrt(pow(" << firstCustomer->get_x() << " - " << afterFirstCustomer->get_x() << ", 2) + pow(" << firstCustomer->get_y() << " - " << afterFirstCustomer->get_y() << ", 2))" << std::endl;
    }
    else if(trip < trip1.size() - 1) {
        Node* beforeFirstCustomer = trip1[customer - 1];
        firstRemoveValue += sqrt(pow(firstCustomer->get_x() - beforeFirstCustomer->get_x(),2) + pow(firstCustomer->get_y() - beforeFirstCustomer->get_y(),2));
        toAddValue += sqrt(pow(unused->get_x() - beforeFirstCustomer->get_x(),2) + pow(unused->get_y() - beforeFirstCustomer->get_y(),2));
        //std::cout << "2 -> sqrt(pow(" << unused->get_x() << " - " << beforeFirstCustomer->get_x() << ", 2) + pow(" << unused->get_y() << " - " << beforeFirstCustomer->get_y() << ", 2))" << std::endl;
        //std::cout << "2.1 -> sqrt(pow(" << firstCustomer->get_x() << " - " << beforeFirstCustomer->get_x() << ", 2) + pow(" << firstCustomer->get_y() << " - " << beforeFirstCustomer->get_y() << ", 2))" << std::endl;
    }

    float canSwap = this->tripsMaxLength[trip] - (this->trips_length[trip] - firstRemoveValue + toAddValue);
    return canSwap > 0;
}

void Solution::swap(int trip, int customer, Node* n2) {
    Node* n1 = this->trips[trip][customer];

    this->trips[trip][customer] = n2;
}

float Solution::getAvaliableLengthIfRemoved(int trip, int customer) {
    this->calculateTripLength();
    double firstRemoveValue = (double)0.0, toAddValue = (double)0.0;
    std::vector<Node*> trip1 = this->trips[trip];
    Node* firstCustomer = trip1[customer];

    if(trip > 0) {
        Node* afterFirstCustomer = trip1[customer + 1];
        firstRemoveValue += sqrt(pow(firstCustomer->get_x() - afterFirstCustomer->get_x(),2) + pow(firstCustomer->get_y() - afterFirstCustomer->get_y(),2));
        //std::cout << "1 -> sqrt(pow(" << unused->get_x() << " - " << afterFirstCustomer->get_x() << ", 2) + pow(" << unused->get_y() << " - " << afterFirstCustomer->get_y() << ", 2))" << std::endl;
        //std::cout << "1.1 -> sqrt(pow(" << firstCustomer->get_x() << " - " << afterFirstCustomer->get_x() << ", 2) + pow(" << firstCustomer->get_y() << " - " << afterFirstCustomer->get_y() << ", 2))" << std::endl;
    }
    else if(trip < trip1.size() - 1) {
        Node* beforeFirstCustomer = trip1[customer - 1];
        firstRemoveValue += sqrt(pow(firstCustomer->get_x() - beforeFirstCustomer->get_x(),2) + pow(firstCustomer->get_y() - beforeFirstCustomer->get_y(),2));
        //std::cout << "2 -> sqrt(pow(" << unused->get_x() << " - " << beforeFirstCustomer->get_x() << ", 2) + pow(" << unused->get_y() << " - " << beforeFirstCustomer->get_y() << ", 2))" << std::endl;
        //std::cout << "2.1 -> sqrt(pow(" << firstCustomer->get_x() << " - " << beforeFirstCustomer->get_x() << ", 2) + pow(" << firstCustomer->get_y() << " - " << beforeFirstCustomer->get_y() << ", 2))" << std::endl;
    }

    float avaliable = this->tripsMaxLength[trip] - (this->trips_length[trip] - firstRemoveValue);
    return avaliable;
}

float Solution::getInsertCost(Node* n1, int trip, int customer) {
    this->calculateTripLength();
    double cost = (double)0.0;
    std::vector<Node*> trip1 = this->trips[trip];

    if(trip > 0) {
        Node* afterFirstCustomer = trip1[customer + 1];
        cost += sqrt(pow(n1->get_x() - afterFirstCustomer->get_x(),2) + pow(n1->get_y() - afterFirstCustomer->get_y(),2));
        //std::cout << "1 -> sqrt(pow(" << unused->get_x() << " - " << afterFirstCustomer->get_x() << ", 2) + pow(" << unused->get_y() << " - " << afterFirstCustomer->get_y() << ", 2))" << std::endl;
        //std::cout << "1.1 -> sqrt(pow(" << firstCustomer->get_x() << " - " << afterFirstCustomer->get_x() << ", 2) + pow(" << firstCustomer->get_y() << " - " << afterFirstCustomer->get_y() << ", 2))" << std::endl;
    }
    else if(trip < trip1.size() - 1) {
        Node* beforeFirstCustomer = trip1[customer - 1];
        cost += sqrt(pow(n1->get_x() - beforeFirstCustomer->get_x(),2) + pow(n1->get_y() - beforeFirstCustomer->get_y(),2));
        //std::cout << "2 -> sqrt(pow(" << unused->get_x() << " - " << beforeFirstCustomer->get_x() << ", 2) + pow(" << unused->get_y() << " - " << beforeFirstCustomer->get_y() << ", 2))" << std::endl;
        //std::cout << "2.1 -> sqrt(pow(" << firstCustomer->get_x() << " - " << beforeFirstCustomer->get_x() << ", 2) + pow(" << firstCustomer->get_y() << " - " << beforeFirstCustomer->get_y() << ", 2))" << std::endl;
    }
    return cost;
}
