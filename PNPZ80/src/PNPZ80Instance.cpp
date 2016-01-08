/* This source file is protected under the GPL License V3. Please view the file
   called "COPYING" to view the license with your rights for this source file and the rest of the PNPZ80 project.
   If the license in the file "COPYING" was not included in this distribution you may find it here: http://www.gnu.org/licenses/gpl.txt*/

#include "PNPZ80Instance.h"
#include "PNPZ80Hardware.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

PNPZ80Instance::PNPZ80Instance()
{
    this->simulator = NULL;
    this->ram = NULL;
    init();
}

PNPZ80Instance::~PNPZ80Instance()
{
    delete this->ram;
    delete this->simulator;
}

void PNPZ80Instance::init()
{
    reset();
}
void PNPZ80Instance::reset()
{
    for (int i = 0; i < 256; i++)
    {
        this->io_addresses[i] = 0;
    }

    if (this->simulator)
    {
        delete this->simulator;
    }

    if (this->ram)
    {
        delete this->ram;
    }

    this->ram = new PNPZ80Ram(0xffff);
    this->simulator = new PNPZ80Simulator(ram);
}

PNPZ80Ram* PNPZ80Instance::getRAM()
{
    return this->ram;
}
void PNPZ80Instance::loadRAMFromBuffer(uint8_t* buf, uint16_t s)
{
    memcpy(this->ram->getBuffer(), buf, s);
}

bool PNPZ80Instance::loadRAMFromFile(const char* filename)
{
    FILE* f = fopen(filename, "r");
    bool ok = false;
    uint32_t fSize;
    fseek(f, 0, SEEK_END);
    fSize = ftell(f);
    rewind(f);
    // Check if the file size is too large
    if (fSize < 0xffff)
    {
        if(fread(this->ram, fSize, 1, f) == fSize)
        {
           ok = true;
        }
    }

    // Close the file
    fclose(f);

    if (ok)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PNPZ80Instance::process()
{
   this->simulator->processOpcode();
}

bool PNPZ80Instance::registerIOAddress(uint8_t addr, PNPZ80Hardware* hardware)
{
    if (this->io_addresses[addr] == NULL)
    {
        this->io_addresses[addr] = hardware;
        std::cout << hardware->getName() << ":" << hardware->getVersion() << " has registered ownership of I/O address: " << (int)addr << std::endl;
        return true;
    }
    else if(this->io_addresses[addr] == hardware)
    {
        // The hardware device has already registered once, so just return true;
          std::cout << hardware->getName() << ":" << hardware->getVersion() << " already registered ownership of I/O address: " << (int)addr << std::endl;
        return true;
    }

    std::cout << hardware->getName() << ":" << hardware->getVersion() << " failed to register ownership of I/O address: " << (int) addr << " as it is already registered by another device" << std::endl;
    return false;
}

void PNPZ80Instance::attachHardware(PNPZ80Hardware* hardware)
{
    hardware->setPNPZ80Instance(this);
    if(hardware->init())
    {
        std::cout << hardware->getName() << ":" << hardware->getVersion() << " has been attached to the Z80 system" << std::endl;
    }
    else
    {
        std::cout << "Failed to attach " << hardware->getName() << ":" << hardware->getVersion() << " to the Z80 system" << std::endl;
    }
    this->hardware.push_back(hardware);
}

PNPZ80Simulator* PNPZ80Instance::getSimulator()
{
    return this->simulator;
}
