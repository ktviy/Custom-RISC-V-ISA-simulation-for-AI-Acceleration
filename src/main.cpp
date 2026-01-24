#include "CPU.h"
#include "ISA.h"
#include <iostream>
#include <vector>

int main() {
    int N;
    std::cout << "Enter vector length N: ";
    std::cin >> N;

    std::vector<uint16_t> vecA(N), vecB(N);
    std::cout << "Enter Vector A:\n";
    for(int i=0; i<N; i++) std::cin >> vecA[i];
    std::cout << "Enter Vector B:\n";
    for(int i=0; i<N; i++) std::cin >> vecB[i];

    uint16_t addrA = 64;
    uint16_t addrB = 128;
    
    // BASELINE (LOAD, MUL, ADD)
    
    CPU cpuBase;

    for (int i = 0; i < N; i++) {
        cpuBase.loadInstruction(addrA + i, vecA[i]); 
        cpuBase.loadInstruction(addrB + i, vecB[i]); 
    };

    cpuBase.setRegisterValue(0, 0);
    cpuBase.setRegisterValue(1, 0);     // i
    cpuBase.setRegisterValue(2, N);     // N
    cpuBase.setRegisterValue(5, addrA); // Pointer A
    cpuBase.setRegisterValue(6, addrB);

    int pcBase = 0;
    
    cpuBase.loadInstruction(pcBase++, (OP_BEQ << 12) | (1 << 9) | (2 << 6) | 9);
    cpuBase.loadInstruction(pcBase++, (OP_LOAD << 12) | (3 << 9) | (5 << 6)); 
    cpuBase.loadInstruction(pcBase++, (OP_LOAD << 12) | (4 << 9) | (6 << 6));
    cpuBase.loadInstruction(pcBase++, (OP_MUL << 12) | (7 << 9) | (3 << 6) | (4 << 3));
    cpuBase.loadInstruction(pcBase++, (OP_ADD << 12) | (0 << 9) | (0 << 6) | (7 << 3));
    cpuBase.loadInstruction(pcBase++, (OP_ADDI << 12) | (1 << 9) | (1 << 6) | 1);
    cpuBase.loadInstruction(pcBase++, (OP_ADDI << 12) | (5 << 9) | (5 << 6) | 1);
    cpuBase.loadInstruction(pcBase++, (OP_ADDI << 12) | (6 << 9) | (6 << 6) | 1);
    cpuBase.loadInstruction(pcBase++, (OP_JMP << 12) | 0);
    
    cpuBase.setPC(0);
    while (cpuBase.getPC() < 9) {
        cpuBase.step();
    };
   
    // NEW ISA (LNM, ACC)2

    CPU cpuNew;
    
    for (int i = 0; i < N; i++) {
        cpuNew.loadInstruction(addrA + i, vecA[i]);
        cpuNew.loadInstruction(addrB + i, vecB[i]);
    };

    cpuNew.setRegisterValue(0, 0); 
    cpuNew.setRegisterValue(1, 0); // i = 0
    cpuNew.setRegisterValue(2, N); 
    cpuNew.setRegisterValue(5, addrA);
    cpuNew.setRegisterValue(6, addrB);

    int pcNew = 0; 

    cpuNew.loadInstruction(pcNew++, (OP_BEQ << 12) | (1 << 9) | (2 << 6) | 5);
    cpuNew.loadInstruction(pcNew++, (OP_LNM << 12) | (3 << 9) | (5 << 6) | (6 << 3)); // store value at R1
    cpuNew.loadInstruction(pcNew++, (OP_ACC << 12) | (0 << 9) | (3 << 5));
    cpuNew.loadInstruction(pcNew++, (OP_ADDI << 12) | (1 << 9) | (1 << 6) | 1);
    cpuNew.loadInstruction(pcNew++, (OP_JMP << 12) | 0);

    cpuNew.setPC(0); 
    while(cpuNew.getPC() < 5) {
        cpuNew.step();
    };
     
    std::cout << "\n----------------------------------------";
    std::cout << "\n[RESULT COMPARISON]";
    std::cout << "\nBaseline Result: " << cpuBase.getRegisterValue(0);
    std::cout << "\nNew ISA Result: " << cpuNew.getRegisterValue(0);
    std::cout << "\n----------------------------------------";
    std::cout << "\n[CYCLE COMPARISON]";
    std::cout << "\nBaseline Cycles: " << cpuBase.getCycles();
    std::cout << "\nNew ISA Cycles:  " << cpuNew.getCycles();
    std::cout << "\nImprovement:     " << (float)(cpuBase.getCycles() - cpuNew.getCycles()) / cpuBase.getCycles() * 100 << "%";
    std::cout << "\n----------------------------------------\n";

    return 0;
}
