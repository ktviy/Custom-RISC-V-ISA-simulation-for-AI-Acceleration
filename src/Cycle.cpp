#include "Cycle.h"
#include <cstdint>

void Cycle::inc(uint16_t c){
    cycles += c;
}
uint16_t Cycle::get() const {
    return cycles;
}
