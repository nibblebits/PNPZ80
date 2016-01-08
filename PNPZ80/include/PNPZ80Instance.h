/* This source file is protected under the GPL License V3. Please view the file
   called "COPYING" to view the license with your rights for this source file and the rest of the PNPZ80 project.
   If the license in the file "COPYING" was not included in this distribution you may find it here: http://www.gnu.org/licenses/gpl.txt*/
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
        PNPZ80Ram* getRAM();

    protected:
    private:
        PNPZ80Ram* ram;
        // Holds pointers to hardware
        std::vector<PNPZ80Hardware*> hardware;
        // Holds pointers to the IO addresses
        PNPZ80Hardware* io_addresses[256];
        PNPZ80Simulator* simulator;
};

#endif // PNPZ80INSTANCE_H
