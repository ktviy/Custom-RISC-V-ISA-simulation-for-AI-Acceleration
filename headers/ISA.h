#ifndef ISA_h
#define ISA_h

enum opcode {
    OP_LOAD = 0x1,
    OP_ADD = 0x2, 
    OP_MUL = 0x3,
    OP_ADDI = 0x4,
    OP_BEQ = 0x5,
    OP_JMP = 0x6,
    OP_LNM = 0xA,
    OP_ACC = 0xB
};

#endif
