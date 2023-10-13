#include "Movement.h"



#ifndef SWAP_HOTELS_H
#define SWAP_HOTELS_H



class SwapHotels : public Movement {
    public:
        SwapHotels(int verbose = 0) {
            this->verbose = verbose;
        };
        ~SwapHotels() {};

        Solution* exec(const Solution* sol) override {
            srand(time(NULL) + seedOffset);
            Solution* copySolution = new Solution(sol);
            int _randomTrip1 = rand() % copySolution->getTrips().size();
            long long memory_kb = getMemoryUsageInKB();
            srand(time(NULL) + (memory_kb % 1000) + seedOffset);
            int _randomTrip2 = rand() % copySolution->getTrips().size();
            if(_randomTrip1 == _randomTrip2) {
                if(_randomTrip1 == copySolution->getTrips().size() - 1) {
                    _randomTrip2--;
                }
                else {
                    _randomTrip2++;
                }
            }
            int _randomHotel = rand() % 2 == 0 ? 0 : copySolution->getTrips()[_randomTrip1].size() - 1;
            Node* hotel1 = copySolution->getTrips()[_randomTrip1][_randomHotel];
            int _randomHotel2 = rand() % 2 == 0 ? 0 : copySolution->getTrips()[_randomTrip2].size() - 1;
            Node* hotel2 = copySolution->getTrips()[_randomTrip2][_randomHotel2];
            std::cout << _randomTrip1 << " " << _randomHotel << " " << _randomTrip2 << " " << _randomHotel2 << " " << std::endl;
            if(verbose == 1) {
                std::cout << "Pre movement" << std::endl;
                std::cout << *copySolution->getTrips()[_randomTrip1][_randomHotel] << std::endl;
                std::cout << *copySolution->getTrips()[_randomTrip2][_randomHotel2] << std::endl;
            }
            copySolution->setSelectedPoint(_randomTrip1, _randomHotel, hotel2);
            copySolution->setSelectedPoint(_randomTrip2, _randomHotel2, hotel1);

            if(_randomTrip1 > 0 && _randomTrip1 < copySolution->getTrips().size() - 1) {
                if(_randomHotel == 0) {
                    copySolution->setSelectedPoint(_randomTrip1 - 1, copySolution->getTrips()[_randomTrip1 - 1].size() - 1, hotel2);
                }
                else {
                    copySolution->setSelectedPoint(_randomTrip1 + 1, 0, hotel2);
                }
            }
            else if(_randomTrip1 == 0) {
                if(_randomHotel != 0) {
                    copySolution->setSelectedPoint(1, 0, hotel2);
                }
            }
            else if(_randomTrip1 == copySolution->getTrips().size() - 1) {
                if(_randomHotel == 0) {
                    copySolution->setSelectedPoint(copySolution->getTrips().size() - 2, copySolution->getTrips()[copySolution->getTrips().size() - 2].size(), hotel2);
                }
            }

            if(_randomTrip2 > 0 && _randomTrip2 < copySolution->getTrips().size() - 1) {
                if(_randomHotel2 == 0) {
                    copySolution->setSelectedPoint(_randomTrip2 - 1, copySolution->getTrips()[_randomTrip2 - 1].size() - 1, hotel1);
                }
                else {
                    copySolution->setSelectedPoint(_randomTrip2 + 1, 0, hotel1);
                }
            }
            else if(_randomTrip2 == 0) {
                if(_randomHotel2 != 0) {
                    copySolution->setSelectedPoint(1, 0, hotel1);
                }
            }
            else if(_randomTrip2 == copySolution->getTrips().size() - 1) {
                if(_randomHotel2 == 0) {
                    copySolution->getTrips()[copySolution->getTrips().size() - 2][copySolution->getTrips()[copySolution->getTrips().size() - 2].size()] = hotel1;
                    copySolution->setSelectedPoint(copySolution->getTrips().size() - 2, copySolution->getTrips()[copySolution->getTrips().size() - 2].size(), hotel1);
                }
            }

            if(verbose == 1) {
                std::cout << "Pós movement" << std::endl;
                std::cout << *copySolution->getTrips()[_randomTrip1][_randomHotel] << std::endl;
                std::cout << *copySolution->getTrips()[_randomTrip2][_randomHotel2] << std::endl;
            }

            return copySolution;
        }

    private:
        int verbose;
};

#endif