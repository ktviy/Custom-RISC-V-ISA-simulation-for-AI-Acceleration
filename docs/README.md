## Custom RISC-V ISA for Dot Product 

## Introduction 
This project is a cycle-accurate C++ simulator that simulates a custom RISC-V instruction set designed to optimize linear algebra. The project focuses on designing and implementing specialized instructions to accelerate the dot product operation, a core mathematical operation in deep learning models. 

This simulator compares two instructions:
1. Baseline ISA: Use the standard instruction (Load, Multiply, Add).
2. Custom ISA: Use fused instructions to minimize latency and increase the throughput. 

## Why Dot Product Optimization
* *Matrix Multiplication* accounts for the majority of the computational workload during the inference phase of transformer architectures.
* **Bottleneck at Memory access** due to latency and bandwidth limitations. Optimizing the dot product increases arithmetic intensity, reducing the number of memory accesses per computation, thereby reducing the pressure on the memory system.
* With Edge AI devices, reducing the number of clock cycles and memory access directly contributes to power savings, extended battery life,..., key factors for embedded systems.

## Methodology
1. Instruction
   * I chose a 16-bit instruction to simulate resource-constrained embedded systems, which can
     + Reducing the amount of memory required, which is crucial for embedded devices such as microcontrollers. Therefore, the program can store more functionality within the same memory space.
     + For matrix computation tasks, 16-bit is sufficient to perform basic operations without wasting resources compared to a 32-bit instruction.

   * Instruction format
| Bits  | 15–12 | 11–9 | 8–6 | 5–3       | 2–0       |
|:-----:|:-----:|:----:|:---:|:---------:|:---------:|
| Field | Opcode| RD   | RS1 | RS2 / Imm | Func / Imm|
      + Opcode: code for each instruction
      + RD: Register Destination
      + RS1, RS2: Register sources
      + Imm, Func: constant value, additional function code

2. Baseline Implementation
   The standard RISC-V approach for the Dot Product loop involves:
     + 'LOAD' element from array A
     + 'LOAD' element from array B
     + 'MUL' multiply the two elements
     + 'ADD' add the result into an accumulator register
     + 'ADDI' increment pointers and loop counter

   Each instructions take 1 clock cycle

3. Custom fused instructions
     + 'LNM': fuses two memory loads and a multiplication into a single instruction cycle, reducing the Instruction Fetch overhead
     + 'ACC': accumulates value directly into a register
-> Custom 2 instructions to keep the instructions simple to optimize the clock frequency
-> Available for resource-constrained embedded chips because the data bus is not wide enough to do all work in 1-2 cycles, leading to CPU stalls.

   Clock cycles:
     + ACC: 1 cycle
     + LNM: 2 cycles
        - If LNM is 1 cycle, the critical path of the hardware will be very long, forcing the CPU to lower its clock speed
      
  ## Performance Benchmarking 
  | Metric | Baseline ISA | Custom ISA | Improvement | 
  | :--- | :---: | :---: | :---: |
  | **Instructions per Loops** | 9 | 5 | **~44%** |
  | **Total cycles (N=100)** | 1000 | 600 | **40% |

