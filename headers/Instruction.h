#ifndef Instruction_h
#define Instruction_h
#include <cstdint>

struct Instruction {
    uint8_t opcode;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    int16_t addr1; 
    int16_t imm;

};

#endif 