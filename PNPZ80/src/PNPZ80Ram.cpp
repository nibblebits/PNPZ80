/* This source file is protected under the GPL License V3. Please view the file
   called "COPYING" to view the license with your rights for this source file and the rest of the PNPZ80 project.
   If the license in the file "COPYING" was not included in this distribution you may find it here: http://www.gnu.org/licenses/gpl.txt*/

#include "PNPZ80Ram.h"

PNPZ80Ram::PNPZ80Ram(uint16_t _size)
{
    this->buf_size = _size;
    this->buf = new char[_size];
}

PNPZ80Ram::~PNPZ80Ram()
{
    delete this->buf;
}


uint8_t PNPZ80Ram::read(uint16_t address)
{
    if (this->doesOverflow(address))
        return 0;

    return this->buf[address];
}

uint16_t PNPZ80Ram::readWord(uint16_t address)
{
    if (this->doesOverflow(address))
        return 0;

    // Little endian format is used in Z80 processors
    return (this->buf[address+1] << 8 | (this->buf[address] & 0xff));
}

bool PNPZ80Ram::write(uint16_t address, uint8_t byte)
{
    if (this->doesOverflow(address))
        return false;

    this->buf[address] = byte;
    return true;
}

bool PNPZ80Ram::writeWord(uint16_t address, uint16_t word)
{
    if (this->doesOverflow(address))
        return false;

    this->buf[address] = word;
    this->buf[address+1] = (word >> 8);
    return true;
}

char* PNPZ80Ram::getBuffer()
{
    return this->buf;
}

bool PNPZ80Ram::doesOverflow(uint16_t address)
{
    if (address >= this->buf_size)
        return true;

    return false;
}
