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
