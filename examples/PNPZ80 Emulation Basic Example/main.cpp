#include <iostream>
#include <PNPZ80.h>
#include "PNPZ80Audio.h"
using namespace std;

int main()
{
    char buf[100] = {0x06, 0x1e, 0x14, 0x0a};
    PNPZ80Instance z80_system;
    // Attach the audio hardware
    z80_system.attachHardware(new PNPZ80Audio());
    z80_system.loadRAMFromBuffer(buf, 100);
    for (int i = 0; i < 3; i++)
        z80_system.process();
    std::cout << "A reg: " << (int)z80_system.getSimulator()->getMainRegister(A_REG) << std::endl;
    std::cout << "E reg:" << (int)z80_system.getSimulator()->getMainRegister(E_REG) << std::endl;
    return 0;
}
