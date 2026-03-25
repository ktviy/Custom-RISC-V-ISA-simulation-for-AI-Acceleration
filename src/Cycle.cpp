#include "Cycle.h"
#include <cstdint>

void Cycle::inc(uint32_t c){
    cycles += c;
}
uint32_t Cycle::get() const {
    return cycles;
}
