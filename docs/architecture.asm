# Register:
# R7: Accumulator (Sum) | R1: Counter (i) | R2: Length (N)
# R5: Pointer A         | R6: Pointer B   | R3, R4: Temporaries

------ BASELINE --------
LOOP:
    BEQ  R1, R2, END      ; 0: If i == N, jump to END (PC = 9)
    LOAD R3, (R5)         ; 1: Load vecA[i] into R3
    LOAD R4, (R6)         ; 2: Load vecB[i] into R4
    MUL  R3, R3, R4       ; 3: R3 = R3 * R4
    ADD  R7, R7, R3       ; 4: R7 = R7 + R3 (Accumulate)
    ADDI R1, R1, 1        ; 5: i = i + 1
    ADDI R5, R5, 1        ; 6: Pointer A++
    ADDI R6, R6, 1        ; 7: Pointer B++
    JMP  Loop             ; 8: Jump back to Loop (PC = 0)
END:
    ; Final result stored in R0


------- NEWLINE --------

# New Instructions: 
# LNM: Load two values, multiply, and auto-increment pointers.
# ACC: Accumulate value into target register.

LOOP:
    BEQ  R1, R2, END      ; 0: If i == N, jump to END (PC=5)
    LNM  R3, (R5+, R6+)   ; 1: R3 = mem[R5] * mem[R6]; R5++; R6++
    ACC  R7, R3           ; 2: R7 = R7 + R3
    ADDI R1, R1, 1        ; 3: i = i + 1
    JMP  Loop             ; 4: Jump back to Loop (PC=0)
END:
    ; Final result stored in R7