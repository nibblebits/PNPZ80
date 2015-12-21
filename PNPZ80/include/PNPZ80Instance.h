#ifndef PNPZ80INSTANCE_H
#define PNPZ80INSTANCE_H

#include <stdint.h>
#include <vector>
#include "PNPZ80.h"
#include "PNPZ80Simulator.h"
class PNPZ80Hardware;
class DLL_EXPORT PNPZ80Instance
{
    public:
        PNPZ80Instance();
        virtual ~PNPZ80Instance();
        void init();
        void reset();
        void process();
        bool registerIOAddress(uint8_t addr, PNPZ80Hardware* hardware);
        void attachHardware(PNPZ80Hardware* hardware);
        void loadRAMFromBuffer(uint8_t* buf, uint16_t s);
        bool loadRAMFromFile(const char* filename);
        PNPZ80Simulator* getSimulator();
        char* getRAM();

    protected:
    private:
        char ram[0xffff];
        // Holds pointers to hardware
        std::vector<PNPZ80Hardware*> hardware;
        // Holds pointers to the IO addresses
        PNPZ80Hardware* io_addresses[256];
        PNPZ80Simulator* simulator;
};

#endif // PNPZ80INSTANCE_H
