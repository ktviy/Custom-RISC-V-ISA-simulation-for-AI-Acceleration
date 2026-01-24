#ifndef CPU_h
#define CPU_h
#include <cstdint>
#include "Register.h"
#include "Memory.h"
#include "Cycle.h"
#include "Instruction.h"
#include <iostream>

class CPU {
public:
    CPU() : PC(0) {};
    void step();
    void loadInstruction(uint16_t addr, uint16_t instruction); // Load an instruction into memory at a specific address
    uint16_t getRegisterValue(uint8_t reg) const {return rs.read(reg);} 
    uint16_t getCycles() const {return cycles.get();}
    void setRegisterValue(uint8_t reg, uint16_t value) { rs.write(reg, value);}
    void setPC(uint16_t value) { PC = value; }
    uint16_t getPC() const {return PC;}


private: 
    RegisterFile rs;
    Memory mem;
    Cycle cycles;
    uint16_t PC; 
};

#endif 
