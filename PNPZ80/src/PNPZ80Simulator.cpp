#include "PNPZ80Simulator.h"
#include <iostream>

PNPZ80Simulator::PNPZ80Simulator(char* ram)
{
    this->ram = ram;
    this->init();
}

PNPZ80Simulator::~PNPZ80Simulator()
{
    //dtor
}

void PNPZ80Simulator::init()
{
    // Reset all registers to zero
    for (int i = 0; i < 8; i++)
    {
        this->m_regs[i] = 0;
    }

    this->PC = 0;
    this->SP = 0xffff;
    this->I = 0;
    this->IX = 0;
    this->IY = 0;
}
uint16_t PNPZ80Simulator::getHL()
{
    return (((uint16_t)this->m_regs[H_REG] << 8) | this->m_regs[L_REG]);
}
uint8_t PNPZ80Simulator::getBC()
{
    return (((uint16_t) this->m_regs[B_REG] << 8) | this->m_regs[C_REG]);
}
uint8_t PNPZ80Simulator::getMainRegister(uint8_t id)
{
    return this->m_regs[id];
}

uint8_t PNPZ80Simulator::getMostSignificantRegister(uint8_t in)
{
    return (in & 0b00111000) >> 3;
}

uint8_t PNPZ80Simulator::getLeastSignificantRegister(uint8_t in)
{
    return (in & 0b00000111);
}

void PNPZ80Simulator::processOpcode()
{
    uint8_t opcode = ram[PC];
    uint8_t b67 = opcode >> 6;
    uint8_t b012 = (opcode & 0b00000111);
    uint8_t b345 = (opcode & 0b00111000) >> 3;
    uint8_t d;
    uint8_t n;
    uint8_t reg;
    uint8_t operand;

    if (opcode == 0) // NOP
    {

    }
    else if(b67 == 0b01 && b345 != 0b110 && b012 != 0b110) // LD r,r'
    {
        this->m_regs[b345] = this->m_regs[b012];
    }
    else if(b67 == 0b00 && b345 != 0b110 && b012 == 0b110) // LD r,n
    {
        this->m_regs[b345] = this->ram[++PC];
    }
    else if(b67 == 0b01 && b345 != 0b110 && b012 == 0b110) // LD r,(HL)
    {
        this->m_regs[b345] = this->ram[this->getHL()];
    }
    else if(opcode == 0b11011101)
    {
        operand = this->ram[++PC];
        reg = this->getMostSignificantRegister(operand);
        d = this->ram[++PC];
        if (operand == 0b00110110) // LD (IX+d),n
        {
            n = this->ram[++PC];
            this->ram[IX+d] = n;
        }
        else if (reg == 0b110) // LD (IX+d), r
        {
            reg = this->getLeastSignificantRegister(operand);
            this->ram[IX+d] = this->m_regs[reg];
        }
        else // LD r,(IX+d)
        {
            this->m_regs[reg] = this->ram[IX+d];
        }
    }
    else if(opcode == 0b11111111) // LD r,(IY+d)
    {
        reg = this->getMostSignificantRegister(this->ram[++PC]);
        d = this->ram[++PC];
        this->m_regs[reg] = this->ram[IY+d];
    }
    else if(opcode == 0b11111101)
    {
        operand = this->ram[++PC];
        d = this->ram[++PC];
        if (operand == 0b00110110) // LD (IY+d), n
        {
            n = this->ram[++PC];
            this->ram[IY+d] = n;
        }
        else // LD (IY+d),r
        {
            reg = this->getLeastSignificantRegister(operand);
            this->ram[IY+d] = this->m_regs[reg];
        }
    }
    else if(opcode == 0b00110110) // LD(HL),n
    {
        n = this->ram[++PC];
        this->ram[this->getHL()] = n;
    }
    else if(b67 == 0b01 && b345 == 0b110 && b012 != 0b110) // LD (HL), r
    {
        this->ram[this->getHL()] = this->m_regs[b012];
    }
    else if(opcode == 0b00001010) // LD A, (BC)
    {
        this->m_regs[A_REG] = this->ram[this->getBC()];
    }
    else
    {
        std::cout << "Bad Opcode: 0x" << std::hex << opcode << std::endl;
    }
    PC++;
}
