#ifndef Register_h
#define Register_h
#include <cstdint>

class RegisterFile {
public: 
    RegisterFile(){
        for (int i = 0; i < 8; i++) regs[i] = 0; 
    };
    uint16_t read(uint8_t reg) const; 
    void write(uint8_t reg, uint16_t value);

private:
    uint16_t regs[8];
};

#endif 
