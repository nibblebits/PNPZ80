#ifndef PNPZ80SIMULATOR_H
#define PNPZ80SIMULATOR_H

#include "PNPZ80.h"
#include <stdint.h>

class DLL_EXPORT PNPZ80Simulator
{
    public:
        PNPZ80Simulator(char* ram);
        virtual ~PNPZ80Simulator();
        void emulate(uint32_t opcode);
        void processOpcode();
        void init();
        uint16_t getHL();
        uint16_t getBC();
        uint16_t getDE();
        uint16_t getIX();
        uint16_t getIY();
        void setRegPair(uint8_t id, uint16_t val);
        uint16_t getRegPair(uint8_t id);
        uint8_t getMainRegister(uint8_t id);
    protected:
    private:
        uint8_t getMostSignificantRegister(uint8_t in);
        uint8_t getLeastSignificantRegister(uint8_t in);
        void b_split(uint8_t byte, uint8_t* b67, uint8_t* b345, uint8_t* b012, uint8_t* b45, uint8_t* b0123);
        char* ram;

        // The regs pointer will point to either the main registers or the alternative registers
        uint8_t* regs;
        // CPU Registers
        uint8_t m_regs[8];
        uint8_t a_regs[8];

        uint16_t PC;
        uint16_t SP;
        uint16_t IX;
        uint16_t IY;
        int8_t I;
        int8_t R;
        // Flip flops
        bool IFF1;
        bool IFF2;

};

#endif // PNPZ80SIMULATOR_H
