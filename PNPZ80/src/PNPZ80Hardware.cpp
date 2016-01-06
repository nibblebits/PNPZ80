/* This source file is protected under the GPL License V3. Please view the file
   called "COPYING" to view the license with your rights for this source file and the rest of the PNPZ80 project.
   If the license in the file "COPYING" was not included in this distribution you may find it here: http://www.gnu.org/licenses/gpl.txt*/

#include "PNPZ80Hardware.h"

PNPZ80Hardware::PNPZ80Hardware(std::string name, std::string version)
{
    //ctor
    this->instance = NULL;
    this->name = name;
    this->version = version;
}

PNPZ80Hardware::~PNPZ80Hardware()
{
    //dtor
}

void PNPZ80Hardware::setPNPZ80Instance(PNPZ80Instance* inst)
{
    this->instance = inst;
}

PNPZ80Instance* PNPZ80Hardware::getPNPZ80Instance()
{
    return this->instance;
}

bool PNPZ80Hardware::registerIOAddress(uint8_t addr)
{
    return this->instance->registerIOAddress(addr, this);
}

std::string PNPZ80Hardware::getName()
{
    return this->name;
}

std::string PNPZ80Hardware::getVersion()
{
    return this->version;
}
