#ifndef Memory_h
#define Memory_h
#include <cstdint>

class Memory {
public:
    Memory() {
        for (int i = 0; i < 256; i++) mem[i] = 0;
    }

    uint16_t load(uint16_t address) const;
    void store(uint16_t address, uint16_t value); 

private: 
    uint16_t mem[256];
};

#endif
