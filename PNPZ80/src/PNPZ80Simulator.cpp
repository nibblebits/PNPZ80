#include "PNPZ80Simulator.h"
#include <iostream>

PNPZ80Simulator::PNPZ80Simulator(char* ram)
{
    this->ram = ram;
    this->regs = this->m_regs;
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
        this->a_regs[i] = 0;
    }

    this->PC = 0;
    this->SP = 0xffff;
    this->I = 0;
    this->R = 0;
    this->IX = 0;
    this->IY = 0;
    this->IFF1 = true;
    this->IFF2 = true;
}
uint16_t PNPZ80Simulator::getHL()
{
    return (((uint16_t)this->regs[H_REG] << 8) | this->regs[L_REG]);
}
uint16_t PNPZ80Simulator::getBC()
{
    return (((uint16_t) this->regs[B_REG] << 8) | this->regs[C_REG]);
}

uint16_t PNPZ80Simulator::getDE()
{
    return (((uint16_t) this->regs[D_REG] << 8) | this->regs[E_REG]);
}

uint16_t PNPZ80Simulator::getIX()
{
    return this->IX;
}

void PNPZ80Simulator::setRegPair(uint8_t id, uint16_t val)
{
    if (id == BC_REG_PAIR)
    {
        this->regs[B_REG] = ((uint16_t) val >> 8);
        this->regs[C_REG] = ((uint16_t) val & 0xff);
    }
    else if(id == DE_REG_PAIR)
    {
        this->regs[D_REG] = ((uint16_t) val >> 8);
        this->regs[E_REG] = ((uint16_t) val & 0xff);
    }
    else if(id == HL_REG_PAIR)
    {
        this->regs[H_REG] = ((uint16_t) val >> 8);
        this->regs[L_REG] = ((uint16_t) val & 0xff);
    }
    else if(id == SP_REG_PAIR)
    {
        this->SP = val;
    }
}
uint16_t PNPZ80Simulator::getRegPair(uint8_t id)
{
    if (id == BC_REG_PAIR)
    {
        return this->getBC();
    }
    else if(id == DE_REG_PAIR)
    {
        return this->getDE();
    }
    else if(id == HL_REG_PAIR)
    {
        return this->getHL();
    }
    else if(id == SP_REG_PAIR)
    {
        return this->SP;
    }

    return 0;
}

uint8_t PNPZ80Simulator::getMainRegister(uint8_t id)
{
    return this->regs[id];
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
    uint8_t b45 = (opcode >> 4) & 0b00000011;
    uint8_t b012 = (opcode & 0b00000111);
    uint8_t b0123 = (opcode & 0b00001111);
    uint8_t b345 = (opcode & 0b00111000) >> 3;
    uint8_t d;
    uint8_t n;
    uint8_t n2;
    uint8_t reg;
    uint8_t operand;
    uint16_t nn;

    if (opcode == 0) // NOP
    {

    }
    else if(b67 == 0b01 && b345 != 0b110 && b012 != 0b110) // LD r,r'
    {
        this->regs[b345] = this->regs[b012];
    }
    else if(b67 == 0b00 && b345 != 0b110 && b012 == 0b110) // LD r,n
    {
        this->regs[b345] = this->ram[++PC];
    }
    else if(b67 == 0b01 && b345 != 0b110 && b012 == 0b110) // LD r,(HL)
    {
        this->regs[b345] = this->ram[this->getHL()];
    }
    else if(opcode == 0b11011101)
    {
        operand = this->ram[++PC];
        reg = this->getMostSignificantRegister(operand);
        if (operand == 0b00110110) // LD (IX+d),n
        {
            d = this->ram[++PC];
            n = this->ram[++PC];
            this->ram[IX+d] = n;
        }
        else if(operand == 0b00100001) // LD IX, nn
        {
            n = this->ram[++PC];
            n2 = this->ram[++PC];
            // Little endian so sort it to big endian
            nn = (n2 << 8) | (n & 0xff);
            this->IX = nn;
        }
        else if (reg == 0b110) // LD (IX+d), r
        {
            d = this->ram[++PC];
            reg = this->getLeastSignificantRegister(operand);
            this->ram[IX+d] = this->regs[reg];
        }
        else // LD r,(IX+d)
        {
            d = this->ram[++PC];
            this->regs[reg] = this->ram[IX+d];
        }
    }
    else if(opcode == 0b11111111) // LD r,(IY+d)
    {
        reg = this->getMostSignificantRegister(this->ram[++PC]);
        d = this->ram[++PC];
        this->regs[reg] = this->ram[IY+d];
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
            this->ram[IY+d] = this->regs[reg];
        }
    }
    else if(opcode == 0b00110110) // LD(HL),n
    {
        n = this->ram[++PC];
        this->ram[this->getHL()] = n;
    }
    else if(b67 == 0b01 && b345 == 0b110 && b012 != 0b110) // LD (HL), r
    {
        this->ram[this->getHL()] = this->regs[b012];
    }
    else if(opcode == 0b00001010) // LD A,(BC)
    {
        this->regs[A_REG] = this->ram[this->getBC()];
    }
    else if(opcode == 0b00011010) // LD A,(DE)
    {
        this->regs[A_REG] = this->ram[this->getDE()];
    }
    else if(opcode == 0b00111010) // LD A,(nn)
    {
        n = this->ram[++PC];
        n2 = this->ram[++PC];
        // Little endian
        nn = (n2 << 8) | n;
        this->regs[A_REG] = this->ram[nn];
    }
    else if(opcode == 0b00000010) // LD (BC),A
    {
        this->ram[this->getBC()] = this->regs[A_REG];
    }
    else if(opcode == 0b00010010) // LD (DE),A
    {
        this->ram[this->getDE()] = this->regs[A_REG];
    }
    else if(opcode == 0b00110010) // LD (nn),A
    {
        n = this->ram[++PC];
        n2 = this->ram[++PC];
        // Little endian
        nn = (n2 << 8) | n;
        this->ram[nn] = this->regs[A_REG];
    }
    else if (opcode == 0b11101101)
    {
        operand = this->ram[++PC];
        if (operand == 0b01010111) // LD A,I
        {
            this->regs[A_REG] = this->I;
            if (this->I < 0)
            {
                this->regs[F_REG] |= S_FLAG;
            }
            else
            {
                this->regs[F_REG] &= ~(S_FLAG);
            }

            if(I == 0)
            {
                this->regs[F_REG] |= Z_FLAG;
            }
            else
            {
                this->regs[F_REG] &= ~(Z_FLAG);
            }

            this->regs[F_REG] |= H_FLAG;

            if(IFF2)
            {
                this->regs[F_REG] |= PV_FLAG;
            }
            else
            {
                this->regs[F_REG] &= ~(PV_FLAG);
            }
            this->regs[F_REG] |= N_FLAG;
        }
        else if(operand == 0b01011111) // LD A,R
        {
            this->regs[A_REG] = this->R;
            if (this->R < 0)
            {
                this->regs[F_REG] |= S_FLAG;
            }
            else
            {
                this->regs[F_REG] &= ~(S_FLAG);
            }

            if(R == 0)
            {
                this->regs[F_REG] |= Z_FLAG;
            }
            else
            {
                this->regs[F_REG] &= ~(Z_FLAG);
            }

            this->regs[F_REG] |= H_FLAG;

            if(IFF2)
            {
                this->regs[F_REG] |= PV_FLAG;
            }
            else
            {
                this->regs[F_REG] &= ~(PV_FLAG);
            }
            this->regs[F_REG] |= N_FLAG;
        }
        else if(operand == 0b01000111) // LD I,A
        {
            this->I = this->regs[A_REG];
        }
        else if(operand == 0b01001111) // LD R,A
        {
            this->R = this->regs[A_REG];
        }
    }
    else if(b67 == 0b00 && b0123 == 0b0001) // LD dd,nn
    {
        n = this->ram[++PC];
        n2 = this->ram[++PC];
        // Little endian so sort it to big endian
        nn = (n2 << 8) | (n & 0xff);
        this->setRegPair(b45, nn);
    }
    else if(opcode == 0b11011101)
    {
        operand = this->ram[++PC];
        if (operand == 0b00100001) // LD IX, nn
        {
            n = this->ram[++PC];
            n2 = this->ram[++PC];
            // Little endian so sort it to big endian
            nn = (n2 << 8) | (n & 0xff);
            this->IX = nn;
        }
    }
    // Last Instruction: LD IX, nn
    else
    {
        std::cout << "Bad Opcode: "  << (int) opcode << std::endl;
    }

    R++;
    PC++;
}
