#include "Algorithm.h"
#include <cmath>
#include <algorithm>

Algorithm::Algorithm(Problem *data) {
    this->data = data; // dados do problema
    this->_tripsLength = data->getTripsLength();

    Solution* solution = new Solution(data);
    this->initial_solution = solution; // solução inicial vazia
}

Algorithm::~Algorithm() {
    this->initial_solution->~Solution();
}

void Algorithm::constructive() {
    std::vector<std::vector<Node*>> solution = this->initial_solution->getTrips(); // lista vazia
    std::vector<Node*> trip;

    std::vector<Node*> CL;

    std::vector<Node*> hotels = this->data->getHotels();
    std::vector<Node*> customers = this->data->getCustomers();

    // hotel H0 inserido na primeira trip
    solution[0].push_back(hotels[0]);

    // Irá rodar para cada trip
     for(int actual_trip_index=0; actual_trip_index<solution.size(); actual_trip_index++) {
        // Avaliar se já está na última trip
        bool isLastTrip = ((solution.size() - actual_trip_index) == 1) ? 1 : 0;
        // Se estiver na última trip irá considerar apenas o hotel H1 como hotel válido.
        if(isLastTrip) {
            hotels.erase(hotels.begin());
            hotels.erase(hotels.begin() + 1, hotels.end());
        }

        // Construir a lista inicial de candidatos e ordená-la
        CL = this->generateCandidateList(solution[actual_trip_index],hotels,customers,actual_trip_index);

        // Enquanto houver candidatos válidos
        while(!CL.empty()) {
            // Selecionar um candidato da lista e adicioná-lo à trip
            solution[actual_trip_index].push_back(CL[0]);
            // Retirar o candidato da lista
            CL.erase(CL.begin());
            
            // Diminuir o tempo da trip
            trip = solution[actual_trip_index];
            this->_tripsLength[actual_trip_index] -= this->calculateTimeBetweenNodes(trip[trip.size()-1],trip[trip.size()-2]);

            // Reconstruir a lista
            CL = this->generateCandidateList(trip,hotels,CL,actual_trip_index);
        }
        // Se a lista estiver vazia, adicionar o Hotel mais próximo
        for(auto hotel : hotels) {
            if((this->_tripsLength[actual_trip_index] - this->calculateTimeBetweenNodes(trip[trip.size()-1],hotel)) >= 0) {
                solution[actual_trip_index].push_back(hotel);
                if(actual_trip_index + 1 < solution.size()) {
                    solution[actual_trip_index + 1].push_back(hotel);
                }
                break;
            }
        }
    }

    this->initial_solution->setSolutionInstance(solution);
}


double Algorithm::calculateTimeBetweenNodes(Node* a, Node* b) {
    return sqrt(pow(a->get_x() - b->get_x(), 2) + pow(a->get_y() - b->get_y(), 2));
}


std::vector<Node*> Algorithm::generateCandidateList(std::vector<Node*> trip, std::vector<Node*> hotels, std::vector<Node*> customers, int actual_trip_index) {
    
    std::vector<Node*> CL; // Lista de candidatos vazia

    // Tempo máximo da trip atual
    double tripMaxTime = this->_tripsLength[actual_trip_index];

    for(auto customer : customers) {
        // Para cada customer:
        // Avaliar o seu benefício para a trip atual
        customer->setActualBenefit(this->localHeuristc(trip[trip.size()-1], customer, tripMaxTime));

        // Avaliar se o tempo dele até algum hotel arbitrário está dentro do tempo da trip atual, se estiver, adicionar na lista de candidatos
        for(auto hotel : hotels) {
            // Leva em consideração o tempo de chegar nesse customer com o nó da trip atual e o tempo do customer chegar ao primeiro hotel possível
            if((tripMaxTime - this->calculateTimeBetweenNodes(customer,hotel) - this->calculateTimeBetweenNodes(customer,trip[trip.size() - 1])) > 0) {
                CL.push_back(customer);
                break;
            }
        }
    }

    // Realizar a odernação com base na heurística escolhida
    if(!CL.empty())
        std::sort(CL.begin(),CL.end(), sortCandidateListBasedOnBenefit);

    return CL;
}

// Heurística local considerando o score do nó e o tempo para alcançar o nó a partir do nó atual.
double Algorithm::localHeuristc(Node* actualNode, Node* b, double tripMaxTime) {
    double time = this->calculateTimeBetweenNodes(actualNode,b);
    double benefit = b->getScore() / time;
    benefit *= (tripMaxTime - time);

    return benefit;
}

bool Algorithm::sortCandidateListBasedOnBenefit(Node* a, Node* b) {
    return a->getBenefit() > b->getBenefit();
}