#ifndef Cycle_h
#define Cycle_h
#include <cstdint> 

class Cycle{
public: 
    void inc(uint16_t c);
    uint16_t get() const; 
private: 
    uint16_t cycles = 0;
};

#endif
