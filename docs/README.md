## Custom RISC-V ISA for Dot Product 
A simulator comparing Baseline vs. Custom fused Instructions for Edge AI applications. 

## Overview

In resource-constrained embedded systems, standard RISC-V instructions (Load, Multiply, Add) often lead to significant overhead in instruction fetching and memory access. This simulator demonstrates how **fused instructions** can minimize latency and increase throughput for Deep Learning workloads.

## Methodology 

### Key Highlights:
* **Cycle-Accurate Modeling:** Precise tracking of clock cycles to reflect hardware behavior.
* **Instruction Fusion:** Reduction of the instruction count per loop by ~44%.
* **Edge-First Design:** 16-bit instruction format to optimize memory footprint and power consumption.

## Why Dot Product Optimization
1. *Matrix Multiplication* accounts for the majority of the computational workload during the inference phase of transformer architectures.
2. **Bottleneck at Memory access** due to latency and bandwidth limitations. Optimizing the dot product increases arithmetic intensity, reducing the number of memory accesses per computation, thereby reducing the pressure on the memory system.
3.  With Edge AI devices, reducing the number of clock cycles and memory access directly contributes to power savings, extended battery life,..., key factors for embedded systems.

### 16-bit Instruction Format
To simulate resource-constrained microcontrollers, a **16-bit word length** was chosen to maximize code density.

| Field | Opcode | RD | RS1 | RS2 / Imm | Func / Imm |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **Bits** | 15–12 | 11–9 | 8–6 | 5–3 | 2–0 |

## ⚡ Custom Instruction Set

We compare a standard RISC-V baseline against a specialized **Fused ISA**:
Our custom design leverages a **Dual-Port Memory architecture**, allowing the CPU to fetch two different operands from memory simultaneously within a single fused instruction.

### 1. Baseline Implementation (Standard RISC-V)
A standard loop requires 5-6 instructions to process a single element pair:
* `LOAD` element from Array A
* `LOAD` element from Array B
* `MUL` elements
* `ADD` to the accumulator
* `ADDI` (Pointer increment & Loop counter)

### 2. Custom Fused Instructions
* **`LNM` (Load-Load-Multiply):** Fuses two memory loads and one multiplication. 
  * *Latency:* 2 cycles (Designed to prevent critical path stretching and maintain high clock frequency).
* **`ACC` (Accumulate):** Directly accumulates the value into a destination register.
  * *Latency:* 1 cycle.

## Performance Benchmarking 
  | Metric | Baseline ISA | Custom ISA | Improvement | 
  | :--- | :---: | :---: | :---: |
  | **Instructions per Loops** | 9 | 5 | **~44%** |
  | **Total cycles (N=100)** | 1000 | 600 | **40%** |

> **Note:** The 40% reduction in cycles significantly lowers energy consumption per inference, a critical factor for embedded AI chips. The architectural trade-off involves using Dual-Port Memory, which increases hardware area but provides substantial speedup for AI workloads.

