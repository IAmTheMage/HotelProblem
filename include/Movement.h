#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "cmath"

#include "Solution.h"
#include <cstdlib>
#include "time.h"
#include <iostream>
#include <fstream>
#include <string>


class Movement {
    public:
        Movement();
        ~Movement();

        virtual Solution* exec(const Solution* sol) {
            Solution* c = new Solution(sol);
            return c;
        }

        void setSeed(int _seed) {
            seedOffset = _seed;
        }

        long long getMemoryUsageInKB() {
            std::ifstream file("/proc/self/status");
            std::string line;
            while (std::getline(file, line)) {
                if (line.compare(0, 6, "VmSize") == 0) {
                    long long memory_kb;
                    if (sscanf(line.c_str(), "VmSize: %lld kB", &memory_kb) == 1) {
                        return memory_kb;
                    }
                }
            }
            return -1; // Return -1 if unable to retrieve memory usage
        }

        static double timeBetweenNodes(Node* a, Node* b) {
            return sqrt(pow(a->get_x() - b->get_x(), 2) + pow(a->get_y() - b->get_y(), 2));
        }

    protected:
        int seedOffset;
};

#endif