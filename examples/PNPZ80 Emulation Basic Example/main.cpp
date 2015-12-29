#include <iostream>
#include <PNPZ80.h>
#include "PNPZ80Audio.h"
using namespace std;

int main()
{
    uint8_t buf[100] = {0xfd, 0x21, 0x6c, 0xea};
    PNPZ80Instance z80_system;
    // Attach the audio hardware
    z80_system.attachHardware(new PNPZ80Audio());
    z80_system.loadRAMFromBuffer(buf, 4);
    for (int i = 0; i < 1; i++)
        z80_system.process();
    std::cout << "A reg: " << (int)z80_system.getSimulator()->getMainRegister(A_REG) << std::endl;
    std::cout << "B reg:" << (int)z80_system.getSimulator()->getMainRegister(B_REG) << std::endl;
    std::cout << "C reg:" << (int)z80_system.getSimulator()->getMainRegister(C_REG) << std::endl;
    std::cout << "F reg:" << (int)z80_system.getSimulator()->getMainRegister(F_REG) << std::endl;
    std::cout << "IX reg: " << (int)z80_system.getSimulator()->getIX() << std::endl;
    std::cout << "IY reg: " << (int)z80_system.getSimulator()->getIY() << std::endl;
    return 0;
}
