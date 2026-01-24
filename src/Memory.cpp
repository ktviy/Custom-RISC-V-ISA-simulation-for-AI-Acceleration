#include "Memory.h"
#include <cstdint>

uint16_t Memory::load(uint16_t address) const {
    return mem[address];
}
void Memory::store(uint16_t address, uint16_t value){
    mem[address] = value; 
}
