#ifndef SWAP_IN_TRIP
#define SWAP_IN_TRIP

#include "Movement.h"
#include "cstdlib"
#include "time.h"

class SwapInTrip : public Movement {
    public:
        SwapInTrip() {};
        ~SwapInTrip(){};

        Solution* exec(const Solution* sol) override {
            bool moving = false;
            Solution* copy = new Solution(sol);
            srand(time(NULL));
            int random = rand() % copy->getTrips().size();
            std::vector<Node*> tour = copy->getTrips()[random];

            bool running = true;

            for(int i = 1; i < copy->getTrips().size() - 1; i++) {
                for(int h = 1; h < copy->getTrips().size() - 1; h++) {
                    if(copy->canSwap(random, random, i, h)) {
                        moving = true;
                        copy->swap(random, random, i, h);
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