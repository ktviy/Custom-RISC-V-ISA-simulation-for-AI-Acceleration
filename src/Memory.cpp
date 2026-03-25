#include "Memory.h"
#include <cstdint>

uint16_t Memory::load(uint16_t address) const {
    if (address >= 256) {
        return 0; 
    }
    return mem[address];
}
void Memory::store(uint16_t address, uint16_t value){
    if (address < 256) {
        mem[address] = value; 
    }
}