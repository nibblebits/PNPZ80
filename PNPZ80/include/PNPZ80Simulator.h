/* This source file is protected under the GPL License V3. Please view the file
   called "COPYING" to view the license with your rights for this source file and the rest of the PNPZ80 project.
   If the license in the file "COPYING" was not included in this distribution you may find it here: http://www.gnu.org/licenses/gpl.txt*/
#ifndef PNPZ80SIMULATOR_H
#define PNPZ80SIMULATOR_H

#include "PNPZ80.h"
#include "PNPZ80Ram.h"

class DLL_EXPORT PNPZ80Simulator
{
    public:
        PNPZ80Simulator(PNPZ80Ram* ram);
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
        uint16_t getWordWithPC();
        void b_split(uint8_t byte, uint8_t* b67, uint8_t* b345, uint8_t* b012, uint8_t* b567, uint8_t* b45, uint8_t* b0123);
        PNPZ80Ram* ram;

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
