#ifndef PNPZ80SIMULATOR_H
#define PNPZ80SIMULATOR_H

#include "PNPZ80.h"
#include <stdint.h>

class DLL_EXPORT PNPZ80Simulator
{
    public:
        PNPZ80Simulator(char* ram);
        virtual ~PNPZ80Simulator();
        void processOpcode();
        void init();
        uint16_t getHL();
        uint8_t getBC();
        uint8_t getMainRegister(uint8_t id);
    protected:
    private:
        uint8_t getMostSignificantRegister(uint8_t in);
        uint8_t getLeastSignificantRegister(uint8_t in);

        char* ram;
        // CPU Registers
        uint8_t m_regs[8];
        uint16_t PC;
        uint16_t SP;
        uint16_t IX;
        uint16_t IY;
        uint8_t I;

};

#endif // PNPZ80SIMULATOR_H
