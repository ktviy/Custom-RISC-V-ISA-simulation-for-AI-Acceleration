#ifndef Cycle_h
#define Cycle_h
#include <cstdint> 

class Cycle{
public: 
    void inc(uint32_t c);
    uint32_t get() const; 
private: 
    uint32_t cycles = 0;
};

#endif