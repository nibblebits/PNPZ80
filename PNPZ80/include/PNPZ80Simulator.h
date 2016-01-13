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
        uint16_t getAF();
        uint16_t getSP();

        uint16_t getMainHL();
        uint16_t getMainBC();
        uint16_t getMainDE();
        uint16_t getMainAF();

        uint16_t getAlternateHL();
        uint16_t getAlternateBC();
        uint16_t getAlternateDE();
        uint16_t getAlternateAF();

        void setHL(uint16_t val);
        void setBC(uint16_t val);
        void setDE(uint16_t val);
        void setIX(uint16_t val);
        void setIY(uint16_t val);
        void setAF(uint16_t val);
        void setSP(uint16_t val);

        void setMainHL(uint16_t val);
        void setMainBC(uint16_t val);
        void setMainDE(uint16_t val);
        void setMainAF(uint16_t val);

        void setAlternateHL(uint16_t val);
        void setAlternateBC(uint16_t val);
        void setAlternateDE(uint16_t val);
        void setAlternateAF(uint16_t val);

        void setRegPair(uint8_t id, uint16_t val, uint8_t pair_type);
        uint16_t getRegPair(uint8_t id, uint8_t pair_type);
        uint8_t getMainRegister(uint8_t id);
    protected:
    private:
        uint8_t getMostSignificantRegister(uint8_t in);
        uint8_t getLeastSignificantRegister(uint8_t in);
        uint16_t getWordWithPC();
        void b_split(uint8_t byte, uint8_t* b67, uint8_t* b345, uint8_t* b012, uint8_t* b567, uint8_t* b45, uint8_t* b0123);
        void push(uint16_t value);
        uint16_t pop();

        //. The logic in this method happens a lot, which is why a method was made for it
        void CPI_CPIR_CPD_CPDR_SetFlags();

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
