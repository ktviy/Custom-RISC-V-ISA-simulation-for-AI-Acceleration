#include "Register.h"
#include <cstdint>

uint16_t RegisterFile::read(uint8_t reg) const {
    return regs[reg]; 
}

void RegisterFile::write(uint8_t reg, uint16_t value) {
    regs[reg] = value;
}
