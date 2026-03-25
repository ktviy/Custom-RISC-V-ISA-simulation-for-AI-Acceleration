#include "Decode.h"
#include "ISA.h"

int16_t signExtend(uint16_t value, int bits) {
    if ((value >> (bits - 1)) & 1) { 
        return value | (0xFFFF << bits); 
    }
    return value; 
}

Instruction decode(uint16_t raw){
    Instruction i{};
    i.opcode = (raw >> 12) & 0xF; // Extract the opcode from the raw instruction

    switch(i.opcode){
        case OP_LOAD: 
            i.rd = (raw >> 9) & 0x7; 
            i.rs1 = (raw >> 6) & 0x7;
            i.addr1 = raw & 0XFF; 
            break;

        case OP_ADD:
            i.rd = (raw >> 9) & 0x7;
            i.rs1 = (raw >> 6) & 0x7;
            i.rs2 = (raw >> 3) & 0x7;
            break;

        case OP_MUL:
            i.rd = (raw >> 9) & 0x7;
            i.rs1 = (raw >> 6) & 0x7;
            i.rs2 = (raw >> 3) & 0x7;
            break;

        case OP_LNM:
            i.rd = (raw >> 9) & 0x7;
            i.rs1 = (raw >> 6) & 0x7;
            i.rs2 = (raw >> 3) & 0x7;
            break;

        case OP_ACC:
            i.rd = (raw >> 9) & 0x7;
            i.rs1 = (raw >> 5) & 0xF;
            break;

        case OP_ADDI:
            i.rd = (raw >> 9) & 0x7;
            i.rs1 = (raw >> 6) & 0x7;
            i.imm = signExtend(raw & 0x3F, 6);
            break;
        
        case OP_BEQ:
            i.rs1 = (raw >> 9) & 0x7;
            i.rs2 = (raw >> 6) & 0x7;
            i.addr1 = signExtend(raw & 0x3F, 6);
            break;
        
        case OP_JMP:
            i.addr1 = signExtend(raw & 0xFFF, 12);
            break;

        default:
            break;

    }
    return i;
}