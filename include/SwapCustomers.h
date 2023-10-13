#ifndef SWAP_CUSTOMERS
#define SWAP_CUSTOMERS

#include "Movement.h"
#include <algorithm>

struct DistanceByNode {
    int index;
    double time;
    double value;
};

bool compareByTime(const DistanceByNode& a, const DistanceByNode& b) {
    return (-a.time + a.value) > (-b.time + b.value);
}

class SwapCustomers : public Movement {
    public:
        SwapCustomers() {};
        ~SwapCustomers() {};

        Solution* exec(const Solution* sol) override {
            Solution* copy = new Solution(sol);
            srand(time(NULL) + getMemoryUsageInKB() + seedOffset);
            int firstTrip = rand() % sol->getTrips().size();
            srand(time(NULL) + getMemoryUsageInKB() + seedOffset);
            int secondTrip = rand() % sol->getTrips().size();
            std::vector<Node*> firstTripData = sol->getTrips()[firstTrip];
            std::vector<Node*> secondTripData = sol->getTrips()[secondTrip];

            std::vector<DistanceByNode> firstTripDistances;
            std::vector<DistanceByNode> secondTripDistances;

            for(int i = 1; i < firstTripData.size() - 1; i++) {
                double previousDistance = 0;
                double nextDistance = 0;
                previousDistance = Movement::timeBetweenNodes(firstTripData[i], firstTripData[i - 1]);
                nextDistance = Movement::timeBetweenNodes(firstTripData[i], firstTripData[i + 1]);
                firstTripDistances.push_back({i, previousDistance + nextDistance, firstTripData[i]->getScore()});
            }

            for(int i = 1; i < secondTripData.size() - 1; i++) {
                double previousDistance = 0;
                double nextDistance = 0;
                previousDistance = Movement::timeBetweenNodes(secondTripData[i], secondTripData[i - 1]);
                nextDistance = Movement::timeBetweenNodes(secondTripData[i], secondTripData[i + 1]);
                secondTripDistances.push_back({i, previousDistance + nextDistance, secondTripData[i]->getScore()});
            }

            std::sort(firstTripDistances.begin(), firstTripDistances.end(), compareByTime);
            std::sort(secondTripDistances.begin(), secondTripDistances.end(), compareByTime);
 
            std::cout << "First score: " << firstTripDistances[0].value << " time: " << firstTripDistances[0].time << std::endl;


            srand(time(NULL) + getMemoryUsageInKB() + seedOffset);
            int firstCustomer = rand() % firstTripData.size() - 2;
            srand(time(NULL) + getMemoryUsageInKB() + seedOffset);
            int secondCustomer = rand() % secondTripData.size() - 2;
            return copy;

        }
};

#endif