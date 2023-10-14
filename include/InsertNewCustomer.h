#ifndef INSERT_NEW_CUSTOMER_H
#define INSERT_NEW_CUSTOMER_H

#include "Movement.h"
#include "algorithm"

bool greaterTime(const DistanceByNode& a, const DistanceByNode& b) {
    return (a.time - a.value) > (b.time - b.value);
}

bool minorTime(const DistanceByNode& a, const DistanceByNode& b) {
    return a.time < b.time;
}

class InsertNewCustomer : public Movement {
    public:
        InsertNewCustomer() {}
        ~InsertNewCustomer() {}
        Solution* exec(const Solution* sol) override {
            bool moving = false;
            Solution* copy = new Solution(sol);
            srand(time(NULL) + getMemoryUsageInKB() + seedOffset);
            int firstTrip = rand() % sol->getTrips().size();
            std::vector<Node*> firstTripData = sol->getTrips()[firstTrip];
            std::vector<DistanceByNode> tripDistances;

            for(int i = 1; i < firstTripData.size() - 1; i++) {
                double previousDistance = 0;
                double nextDistance = 0;
                previousDistance = Movement::timeBetweenNodes(firstTripData[i], firstTripData[i - 1]);
                nextDistance = Movement::timeBetweenNodes(firstTripData[i], firstTripData[i + 1]);
                tripDistances.push_back({i, previousDistance + nextDistance, firstTripData[i]->getScore()});
            }
            std::sort(tripDistances.begin(), tripDistances.end(), greaterTime);

            DistanceByNode greater = tripDistances[0];
            std::vector<Node*> unuseds = copy->getUnusedCostumers();
            float avaliableValue = copy->getAvaliableLengthIfRemoved(firstTrip, greater.index);
            int index = 0;
            std::vector<DistanceByNode> unusedsDistances;
            int current = 0;
            for(Node* unused : unuseds) {
                double previousDistance = 0;
                double nextDistance = 0;
                previousDistance = (double)copy->getInsertCost(unused, firstTrip, greater.index);
                unusedsDistances.push_back({current, previousDistance + nextDistance, 0});
                current++;
            }

            std::sort(unusedsDistances.begin(), unusedsDistances.end(), minorTime);
            for(DistanceByNode unusedDistance : unusedsDistances) {
                Node* unused = unuseds[unusedDistance.index];
                if(copy->getInsertCost(unused, firstTrip, greater.index) < avaliableValue) {
                    moving = true;
                    if(index == 0) {
                        copy->removeUnused(unusedDistance.index);
                        copy->addUnused(copy->getTrips()[firstTrip][greater.index]);
                        copy->swap(firstTrip, greater.index, unused);
                        index++;
                        avaliableValue -= copy->getInsertCost(unused, firstTrip, greater.index);
                    }
                    else {
                        copy->removeUnused(unusedDistance.index);
                        copy->insertIn(unused, firstTrip, greater.index + index);
                        avaliableValue -= copy->getInsertCost(unused, firstTrip, greater.index);
                        index++;
                    }
                }
                else {
                    break;
                }
            }
            //if(moving) std::cout << "Movimento efetuado" << std::endl;
            copy->calculateSolutionScore();
            return copy;

        }
};

#endif