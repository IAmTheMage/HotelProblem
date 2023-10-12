#include "Algorithm.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>

Algorithm::Algorithm(Problem *data) {
    this->data = data; // dados do problema
    this->_tripsLength = data->getTripsLength();

    Solution* solution = new Solution(data);
    this->initial_solution = solution; // solução inicial vazia
    this->best_solution = solution;

    // Inicia o gerador de números aleatórios
    std::srand(std::time(0));
}

Algorithm::~Algorithm() {
    this->initial_solution->~Solution();
}

double Algorithm::calculateSolutionQuality(std::vector<std::vector<Node*>> solution) {
    double quality = 0.0;
    for(auto trip : solution) {
        for(auto node : trip) {
            quality += node->getScore();
        }
    }
    return quality;
}

// @param número de iterações do reativo, tamanho do bloco, quantidade de iterações da fase randomica
void Algorithm::adaptativeRandomGreedy(int numIter, int block, int randomGreedyNumIter) {
    std::vector<std::vector<Node*>> bestSolution = this->initial_solution->getTrips(); // lista vazia
    std::vector<std::vector<Node*>> solution = this->initial_solution->getTrips(); // lista vazia

    std::vector<float> alphas; //vetor dos valores alphas considerados
    this->setAlphas(alphas);

    std::vector<double> medians; //Vetor de médias
    std::vector<double> sums; // Vetor de somas (suporte para as médias)
    std::vector<double> bestSolutions; // Vetor para armazenar a melhor solução para cada alfa
    std::vector<double> probabilities;
    std::vector<double> q; // Suporte para atualização de probabilidades de cada alfa
    std::vector<int> solutionsAmount;

    int index;
    double alpha_quality;

    int alphas_size = alphas.size();

    // Inicialização dos vetores de suporte
    for(int i = 0; i < alphas_size; i++) {
      bestSolutions.push_back(0.0f);
      q.push_back(0.0f);
      sums.push_back(0.0f);
      solutionsAmount.push_back(0);
    }

    this->initializeVectors(medians,probabilities,alphas_size);

    for(int i=1; i<(numIter+1); i++) {
        if(i % block == 0) {
            this->updateProbabilities(medians,probabilities,bestSolutions,q); // Atualização das probabilidades
        }
        index = this->selectProbabilitie(probabilities); // Seleção do índice do valor alpha
        solution = this->randomGreedy(alphas[index], randomGreedyNumIter); // geração da melhor solução do randomizado
        alpha_quality = this->calculateSolutionQuality(solution);
        this->updateMedians(medians, alpha_quality, alphas, sums, alphas[index], solutionsAmount); // Atualização das médias

        if(bestSolutions[index] < alpha_quality) {
            bestSolutions[index] = alpha_quality; // Atualização da qualidade do i-ésimo valor alpha
        }
        if(this->calculateSolutionQuality(this->best_solution->getTrips()) < this->calculateSolutionQuality(solution)) {
            this->best_solution->setSolutionInstance(solution);
        }
    }

    std::cout << "Guloso Randomizado Reativo finalizado!\n";
}

void Algorithm::setAlphas(std::vector<float>& alphas) {
    alphas.push_back(0.05);
    alphas.push_back(0.09);
    alphas.push_back(0.13);
    alphas.push_back(0.21);
    alphas.push_back(0.28);
    alphas.push_back(0.39);
    alphas.push_back(0.51);
    alphas.push_back(0.78);
    alphas.push_back(0.57);
    alphas.push_back(0.81);
}

void Algorithm::updateProbabilities(std::vector<double>& median, std::vector<double>& probabilities, std::vector<double>& bestSolutions, std::vector<double>& q) {
    float somaQ = 0.0f;
    for(int i = 0; i < median.size(); i++) {
      float tmp =  bestSolutions[i] / median[i];
      q[i] = pow((tmp), 100);
      somaQ += q[i];
    }
    for(int i = 0; i < median.size(); i++) {
      if(q[i] / somaQ != 0.0f)
      probabilities[i] = q[i] / somaQ;
    }
}

int Algorithm::selectProbabilitie(std::vector<double>& prob) {
    std::vector<int> indexes;
    for(int i = 0; i < prob.size(); i++) {
      for(int j = 0; j < (int)(prob[i] * 100); j++) {
        indexes.push_back(i);
      }
    }
    int random = rand() % indexes.size();
    return indexes[random];
}

void Algorithm::updateMedians(std::vector<double>& medians, double solution, std::vector<float> alphas,  std::vector<double> sums, float alpha, std::vector<int> solutionsAmount) {
    int index;
    for(int i = 0; i < alphas.size(); i++) {
      if(alpha == alphas[i]) {
        index = i;
        break;
      } 
    }
    sums[index] += solution;
    solutionsAmount[index] += solutionsAmount[index] + 1;
    medians[index] = sums[index] / solutionsAmount[index];
}

void Algorithm::initializeVectors(std::vector<double>& medians, std::vector<double>& prob, int size) {
    double baseProbability = 1.0f / size;
    double baseMedian = 1.0f;
    for(int i = 0; i < size; i++) {
      prob.push_back(baseProbability);
      medians.push_back(baseMedian);
    }
}

std::vector<std::vector<Node*>> Algorithm::randomGreedy(float alpha, int iter) {
    std::vector<std::vector<Node*>> solution;
    solution.resize(data->getTripsAmount(), std::vector<Node*>()); // lista vazia

    std::vector<std::vector<Node*>> best_solution = solution; // lista vazia

    this->_tripsLength = this->data->getTripsLength();
    best_solution = this->randomGreedyIter(alpha);

    for(int i=1; i<iter; i++) {
        this->_tripsLength = this->data->getTripsLength();
        this->_tripsLength = this->data->getTripsLength();
        solution = this->randomGreedyIter(alpha);
        if(this->calculateSolutionQuality(solution) > this->calculateSolutionQuality(best_solution)) {
            best_solution = solution;
        }
    }

    return best_solution;
}

std::vector<std::vector<Node*>> Algorithm::randomGreedyIter(float alpha) {
    std::vector<std::vector<Node*>> solution;
    solution.resize(data->getTripsAmount(), std::vector<Node*>());
    std::vector<Node*> trip;
    int random_index;
    Node *aux;

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
            hotels.erase(hotels.begin(), hotels.end()-1);
        }

        // Construir a lista inicial de candidatos e ordená-la
        CL = this->generateCandidateList(solution[actual_trip_index],hotels,customers,actual_trip_index);

        // Enquanto houver candidatos válidos
        while(!CL.empty()) {
            // Índice aleatório
            random_index = static_cast<int>(alpha*CL.size());
            if(random_index!=0)
                random_index = std::rand() % random_index;
            // Selecionar um candidato da lista e adicioná-lo à trip
            solution[actual_trip_index].push_back(CL[random_index]);
            // Retirar o candidato da lista
            CL.erase(CL.begin()+random_index);
            
            // Diminuir o tempo da trip
            trip = solution[actual_trip_index];
            this->_tripsLength[actual_trip_index] -= this->calculateTimeBetweenNodes(trip[trip.size()-1],trip[trip.size()-2]);

            // Reconstruir a lista
            CL = this->generateCandidateList(trip,hotels,CL,actual_trip_index);
        }
        // Se a lista estiver vazia, adicionar o Hotel mais próximo
        for(auto hotel : hotels) {
            aux = trip[trip.size()-1];
            if((this->_tripsLength[actual_trip_index] - this->calculateTimeBetweenNodes(aux,hotel)) >= 0) {
                solution[actual_trip_index].push_back(hotel);
                if(actual_trip_index + 1 < solution.size()) {
                    solution[actual_trip_index + 1].push_back(hotel);
                }
                break;
            }
        }
    }

    //this->initial_solution->setSolutionInstance(solution);
    return solution;
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