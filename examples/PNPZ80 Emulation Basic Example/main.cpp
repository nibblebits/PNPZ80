/* This source file is protected under the GPL License V3. Please view the file
   called "COPYING" to view the license with your rights for this source file and the rest of the PNPZ80 project.
   If the license in the file "COPYING" was not included in this distribution you may find it here: http://www.gnu.org/licenses/gpl.txt*/
#include <iostream>
#include <PNPZ80.h>
#include "PNPZ80Audio.h"
using namespace std;

int main()
{
    // Machine instructions for the Z80 assemblers
    uint8_t buf[100] = {0x31, 0x07, 0x10, 0x11, 0x33, 0x22, 0xd5};
    PNPZ80Instance z80_system;

    // Attach the audio hardware
    z80_system.attachHardware(new PNPZ80Audio());
    z80_system.loadRAMFromBuffer(buf, 100);
    for (int i = 0; i < 3; i++)
        z80_system.process();
    std::cout << "A reg: " << (int)z80_system.getSimulator()->getMainRegister(A_REG) << std::endl;
    std::cout << "B reg:" << (int)z80_system.getSimulator()->getMainRegister(B_REG) << std::endl;
    std::cout << "C reg:" << (int)z80_system.getSimulator()->getMainRegister(C_REG) << std::endl;
    std::cout << "F reg:" << (int)z80_system.getSimulator()->getMainRegister(F_REG) << std::endl;
    std::cout << "IX reg: " << (int)z80_system.getSimulator()->getIX() << std::endl;
    std::cout << "IY reg: " << (int)z80_system.getSimulator()->getIY() << std::endl;
    std::cout << "HL regs: " << (int)z80_system.getSimulator()->getRegPair(HL_REG_PAIR_DD, PAIR_TYPE_DD) << std::endl;
    std::cout << "DE regs: " << (int)z80_system.getSimulator()->getRegPair(DE_REG_PAIR_DD, PAIR_TYPE_DD) << std::endl;
    std::cout << "BC regs: " << (int)z80_system.getSimulator()->getRegPair(BC_REG_PAIR_DD, PAIR_TYPE_DD) << std::endl;
    std::cout << "SP regs: " << (int)z80_system.getSimulator()->getRegPair(SP_REG_PAIR_DD, PAIR_TYPE_DD) << std::endl;
    std::cout << "memory 4102: " << (int) z80_system.getRAM()->read(4102) << std::endl;
    std::cout << "memory 4101: " << (int) z80_system.getRAM()->read(4101) << std::endl;
    return 0;
}
