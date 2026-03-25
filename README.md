# RISC-V Custom ISA Simulator for Dot-Product Optimization
> **A cycle-accurate C++ simulator achieving 40% cycle reduction for Edge AI workloads.**

---

## Baseline vs. Optimized ISA

| Standard RISC-V (9 instructions/loop) | Custom ISA (5 instructions/loop) |
| :--- | :--- |
| `LW t0, 0(a0)`  *(Load A)* | **`LNM t0, (a0), (a1)`** *(Fused Load-Load-Mul)* |
| `LW t1, 0(a1)`  *(Load B)* | **`ACC s0, t0`** *(Direct Accumulate)* |
| `MUL t2, t0, t1` *(Multiply)* | `ADDI a0, a0, 2` |
| `ADD s0, s0, t2` *(Accumulate)* | `ADDI a1, a1, 2` |
| `ADDI a0, a0, 4` | `BNE t3, zero, loop` |
| ... (plus loop overhead) | |
| ❌ **High Fetch & Memory Overhead** | ✅ **Minimal Cycles & Fused Execution** |

---

## Performance Benchmarking (N=100)

| Metric | Baseline ISA | Custom ISA | **Improvement** |
| :--- | :---: | :---: | :---: |
| **Instructions per Loop** | 9 | 5 | **~44% Reduction** |
| **Total Clock Cycles** | 1000 | 600 | **40% Speedup** |

> **Improvement:** By reducing instruction count and cycles, this architecture significantly lowers energy consumption per inference—a critical requirement for **Edge AI** and **Battery-powered embedded systems**.

---

## Architectural Design

### 1. Dual-Port Memory Integration
Unlike standard single-port memory, this simulator assumes a **Dual-Port RAM** architecture. This allows the `LNM` instruction to fetch two operands (from Array A and Array B) simultaneously in one clock cycle, effectively doubling the memory bandwidth for linear algebra tasks.

### 2. 16-bit Custom Instruction Format
Designed for resource-constrained microcontrollers to maximize code density and reduce memory footprint.

| Field | Opcode | RD | RS1 | RS2 / Imm | Func / Imm |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **Bits** | 15–12 | 11–9 | 8–6 | 5–3 | 2–0 |

### 3. Cycle-Accurate Execution Logic
* **`LNM` (Load-Load-Multiply):** 2 Cycles. *Note: We assigned 2 cycles to prevent the Critical Path from becoming too long, ensuring the CPU can maintain a high clock frequency ($f_{max}$).*
* **`ACC` (Accumulate):** 1 Cycle. Directly adds the product to the destination register.

---

## Trade-offs
* **Performance vs. Area:** Using Dual-Port RAM increases the hardware area (silicon cost) but provides a massive 40% boost in computational efficiency for Transformer-based models.
* **ISA Complexity:** Fusing instructions increases decoder complexity but drastically reduces "Instruction Fetch" energy, which is often more expensive than the execution itself in embedded chips.

---
