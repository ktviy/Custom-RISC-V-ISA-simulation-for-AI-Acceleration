#include "ALU.h"
#include <cstdint>

int16_t ALU::ADD(int16_t a, int16_t b){
    return a + b;
}
int16_t ALU::MUL(int16_t a, int16_t b){
    return int32_t(a) * int32_t(b);
}
