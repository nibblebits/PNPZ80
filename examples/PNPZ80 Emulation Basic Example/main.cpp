#include <iostream>
#include <PNPZ80.h>
#include "PNPZ80Audio.h"
using namespace std;

int main()
{
    char buf[100] = {0x3a, 0x32, 0x88};
    PNPZ80Instance z80_system;
    // Attach the audio hardware
    z80_system.attachHardware(new PNPZ80Audio());
    z80_system.loadRAMFromBuffer(buf, 100);
    for (int i = 0; i < 1; i++)
        z80_system.process();
    std::cout << "A reg: " << (int)z80_system.getSimulator()->getMainRegister(A_REG) << std::endl;
    std::cout << "B reg:" << (int)z80_system.getSimulator()->getMainRegister(B_REG) << std::endl;
    std::cout << "C reg:" << (int)z80_system.getSimulator()->getMainRegister(C_REG) << std::endl;
    return 0;
}
