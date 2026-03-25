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
            int16_t sum = ALU::ADD((int16_t)rs.read(instr.rs1), (int16_t)rs.read(instr.rs2));
            rs.write(instr.rd, (uint16_t) sum); 
            cycles.inc(1);
            break; 
        }

        case OP_ADDI: {
            int16_t offset = (int16_t)rs.read(instr.rs1) + instr.imm;
            rs.write(instr.rd, (uint16_t)offset);
            cycles.inc(1);
            break;
        }

        case OP_BEQ: {
            if ((int16_t)rs.read(instr.rs1) == (int16_t)rs.read(instr.rs2)) {
                int32_t next_pc = (int32_t)PC + (int32_t)instr.addr1;
                if (next_pc < 0) {
                    PC = 0;
                } else {
                    PC = (uint16_t)next_pc;
                }
            }
            cycles.inc(1);
            break;
        }

        case OP_JMP: {
            int32_t next_pc = (int32_t)PC + (int32_t)instr.addr1;
            if (next_pc < 0) {
                PC = 0; 
            } else {
                PC = (uint16_t)next_pc;
            }
            cycles.inc(1);
            break;
        }

        case OP_MUL: 
        {
            int16_t mul = (int16_t)ALU::MUL((int16_t)rs.read(instr.rs1), (int16_t)rs.read(instr.rs2));
            rs.write(instr.rd, (uint16_t)mul);
            cycles.inc(2);
            break; 
        }

        case OP_LNM: 
        {
            uint16_t addr1 = rs.read(instr.rs1);
            uint16_t addr2 = rs.read(instr.rs2);
            int16_t val1 = (int16_t)mem.load(addr1); 
            int16_t val2 = (int16_t)mem.load(addr2); 
            int16_t mul = (int16_t)ALU::MUL(val1, val2); 
            rs.write(instr.rd, (uint16_t)mul);
            rs.write(instr.rs1, addr1 + 1);
            rs.write(instr.rs2, addr2 + 1);
            cycles.inc(2);
            break;
        }

        case OP_ACC:
        {
            int16_t current_sum = (int16_t)rs.read(instr.rd);
            int16_t new_sum = (int16_t)rs.read(instr.rs1);
            rs.write(instr.rd, (uint16_t)(current_sum + new_sum));
            cycles.inc(1);
            break; 
        }
            
        default:
            break;
        };
    
    
}