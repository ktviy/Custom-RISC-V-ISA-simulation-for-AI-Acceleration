import matplotlib.pyplot as plt
import numpy as np

N = np.array([10, 20, 50, 100])
baseline_cycles = N * 10  
newline_cycles = N * 6   

plt.figure(figsize=(10, 6))
plt.plot(N, baseline_cycles, label='Baseline ISA (9 inst/loop)', marker='o', linewidth=2)
plt.plot(N, newline_cycles, label='Newline ISA Optimized (5 inst/loop)', marker='s', linewidth=2)

plt.title('Performance Comparison: Baseline vs Optimized ISA', fontsize=14)
plt.xlabel('Vector Length (N)', fontsize=12)
plt.ylabel('Total Execution Cycles', fontsize=12)
plt.legend()
plt.grid(True, linestyle='--')
plt.savefig('benchmarking.png')
plt.show()
