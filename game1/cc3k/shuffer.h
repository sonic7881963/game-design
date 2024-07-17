
#ifndef SHUFFER_H
#define SHUFFER_H
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class Shuffer {
public:
    static int getLuckNum(size_t size){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng {seed};

        std::vector<int> q ;
        for(size_t i = 0; i < size; i++){
            q.push_back(i);
        }
        std::shuffle( q.begin(), q.end(), rng );
        return q[0];
    }

};


#endif

