#include "CPU.h"
#include "Decode.h"
#include "ALU.h"
#include "ISA.h"
#include <iostream>
#include <cstdint>


void CPU::loadInstruction(uint16_t addr, uint16_t instruction){
    mem.store(addr, instruction);
}


void CPU::step(){
    uint16_t raw =  mem.load(PC);
    PC++;
    Instruction instr = decode(raw);

     // execute the instruction
    switch(instr.opcode){
        case OP_LOAD:
        {
            uint16_t addr = rs.read(instr.rs1);
            uint16_t val = mem.load(addr);
            rs.write(instr.rd, val);
            cycles.inc(1);
            break; 
        }

        case OP_ADD: 
        {
            uint16_t sum = ALU::ADD(rs.read(instr.rs1), rs.read(instr.rs2));
            rs.write(instr.rd, sum); 
            cycles.inc(1);
            break; 
        }

        case OP_ADDI: {
            uint16_t offset = rs.read(instr.rs1) + instr.imm;
            rs.write(instr.rd, offset);
            cycles.inc(1);
            break;
        }

        case OP_BEQ: {
            if (rs.read(instr.rs1) == rs.read(instr.rs2)) {
                PC = instr.addr1; 
            }
            cycles.inc(1);
            break;
        }

        case OP_JMP: {
            PC = instr.addr1; // Nhảy không điều kiện
            cycles.inc(1);
            break;
        }

        case OP_MUL: 
        {
            uint16_t mul = ALU::MUL(rs.read(instr.rs1), rs.read(instr.rs2));
            rs.write(instr.rd, mul);
            cycles.inc(2);
            break; 
        }

        case OP_LNM: 
        {
            uint16_t addr1 = rs.read(instr.rs1);
            uint16_t addr2 = rs.read(instr.rs2);
            uint16_t val1 = mem.load(addr1); 
            uint16_t val2 = mem.load(addr2); 
            uint16_t mul = ALU::MUL(val1, val2); 
            rs.write(instr.rd, mul);
            rs.write(instr.rs1, addr1 + 1);
            rs.write(instr.rs2, addr2 + 1);
            cycles.inc(2);
            break;
        }

        case OP_ACC:
        {
            uint16_t current_sum = rs.read(instr.rd);
            uint16_t new_sum = rs.read(instr.rs1);
            rs.write(instr.rd, current_sum + new_sum);
            cycles.inc(1);
            break; 
        }
            
        default:
            break;
        };
    

    
}
