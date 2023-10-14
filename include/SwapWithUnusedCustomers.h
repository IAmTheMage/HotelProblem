#ifndef SWAP_WITH_UNUSED_COSTUMERS_H
#define SWAP_WITH_UNUSED_COSTUMERS_H
#include "Movement.h"
#include <algorithm>

bool compareByTime2(const DistanceByNode& a, const DistanceByNode& b) {
    return (a.time + a.value) > (b.time + b.value);
}


class SwapWithUnusedCostumers : public Movement {
    public:
        SwapWithUnusedCostumers() {};
        ~SwapWithUnusedCostumers() {};

        Solution* exec(const Solution* sol) {
            Solution* copy = new Solution(sol);
            srand(time(NULL) + getMemoryUsageInKB() + seedOffset);
            int firstTrip = rand() % sol->getTrips().size();
            std::vector<Node*> firstTripData = sol->getTrips()[firstTrip];

            std::vector<DistanceByNode> firstTripDistances;

            for(int i = 1; i < firstTripData.size() - 1; i++) {
                double previousDistance = 0;
                double nextDistance = 0;
                previousDistance = Movement::timeBetweenNodes(firstTripData[i], firstTripData[i - 1]);
                nextDistance = Movement::timeBetweenNodes(firstTripData[i], firstTripData[i + 1]);
                firstTripDistances.push_back({i, previousDistance + nextDistance, firstTripData[i]->getScore()});
            }

            std::sort(firstTripDistances.begin(), firstTripDistances.end(), compareByTime2);

            bool running = true;
            for(DistanceByNode dist : firstTripDistances) {
                for(Node* node : copy->getUnusedCostumers()) {
                    if(copy->canSwap(firstTrip, dist.index, node)) {
                        copy->swap(firstTrip, dist.index, node);
                        running = false;
                        break;
                    }
                }
                if(!running) break;
            }
            return copy;

        }

};

#endif