#ifndef PNPZ80RAM_H
#define PNPZ80RAM_H

#include "PNPZ80.h"

class DLL_EXPORT PNPZ80Ram
{
    public:
        PNPZ80Ram(uint16_t _size);
        virtual ~PNPZ80Ram();

        uint8_t read(uint16_t address);
        uint16_t readWord(uint16_t address);
        bool write(uint16_t address, uint8_t byte);
        bool writeWord(uint16_t address, uint16_t word);
        char* getBuffer();
    protected:
    private:
        uint16_t buf_size;
        char* buf;

        // Used to check that the address is in the bounds of the buffer
        bool doesOverflow(uint16_t address);
};

#endif // PNPZ80RAM_H
