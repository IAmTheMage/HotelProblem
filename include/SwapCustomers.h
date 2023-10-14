#ifndef SWAP_CUSTOMERS
#define SWAP_CUSTOMERS

#include "Movement.h"
#include <algorithm>

bool compareByTime(const DistanceByNode& a, const DistanceByNode& b) {
    return (a.time + a.value) > (b.time + b.value);
}

class SwapCustomers : public Movement {
    public:
        SwapCustomers() {};
        ~SwapCustomers() {};

        Solution* exec(const Solution* sol) override {
            bool moving = false;
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

            bool running = true;
            for(DistanceByNode dist : firstTripDistances) {
                for(DistanceByNode dist2 : secondTripDistances) {
                    if(copy->canSwap(firstTrip, secondTrip, dist.index, dist2.index)) {
                        moving = true;
                        copy->swap(firstTrip, secondTrip, dist.index, dist2.index);
                        running = false;
                        break;
                    }
                }
                if(!running) break;
            }
            //if(moving) std::cout << "Movimento efetuado" << std::endl;
            copy->calculateSolutionScore();
            return copy;

        }
};

#endif