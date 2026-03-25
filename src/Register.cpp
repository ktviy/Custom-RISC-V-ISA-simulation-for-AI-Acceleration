#include "Register.h"
#include <cstdint>

uint16_t RegisterFile::read(uint8_t reg) const {
    return regs[reg]; 
}

void RegisterFile::write(uint8_t reg, uint16_t value) {
    if (reg == 0) return; // Register 0 is hardwired to 0
    regs[reg] = value;
}