/* This source file is protected under the GPL License V3. Please view the file
   called "COPYING" to view the license with your rights for this source file and the rest of the PNPZ80 project.
   If the license in the file "COPYING" was not included in this distribution you may find it here: http://www.gnu.org/licenses/gpl.txt*/

#include "PNPZ80Simulator.h"
#include <iostream>
PNPZ80Simulator::PNPZ80Simulator(PNPZ80Ram* ram)
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

uint16_t PNPZ80Simulator::getIY()
{
    return this->IY;
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

void PNPZ80Simulator::b_split(uint8_t byte, uint8_t* b67, uint8_t* b345, uint8_t* b012, uint8_t* b45, uint8_t* b0123)
{
    if (b67 != NULL)
        *b67 = byte >> 6;
    if (b45 != NULL)
        *b45 = (byte >> 4) & 0b00000011;
    if (b012 != NULL)
        *b012 = (byte & 0b00000111);
    if (b0123 != NULL)
        *b0123 = (byte & 0b00001111);
    if (b345 != NULL)
        *b345 = (byte & 0b00111000) >> 3;
}

uint16_t PNPZ80Simulator::getWordWithPC()
{
    uint8_t n;
    uint8_t n2;
    n = this->ram->read(++PC);
    n2 = this->ram->read(++PC);
    return (n2 << 8) | (n & 0xff);
}

void PNPZ80Simulator::processOpcode()
{
    uint8_t opcode = this->ram->read(PC);
    emulate(opcode);
    PC++;
}

void PNPZ80Simulator::emulate(uint32_t opcode)
{
    uint8_t b67;
    uint8_t b45;
    uint8_t b012;
    uint8_t b0123;
    uint8_t b345;
    uint8_t d;
    uint8_t n;
    uint8_t reg;
    uint8_t operand;
    uint16_t nn;
    uint16_t result;

    // Split the bits of the opcode and store them in the bit variables
    b_split(opcode, &b67, &b345, &b012, &b45, &b0123);

    if (opcode == 0) // NOP
    {

    }
    else if(b67 == 0b01 && b345 != 0b110 && b012 != 0b110) // LD r,r'
    {
        this->regs[b345] = this->regs[b012];
    }
    else if(b67 == 0b00 && b345 != 0b110 && b012 == 0b110) // LD r,n
    {
        this->regs[b345] = this->ram->read(++PC);
    }
    else if(b67 == 0b01 && b345 != 0b110 && b012 == 0b110) // LD r,(HL)
    {
        this->regs[b345] = this->ram->read(this->getHL());
    }
    else if(opcode == 0b11011101)
    {
        operand = this->ram->read(++PC);

        // Bit split the óperand
        b_split(operand, &b67, &b345, &b012, &b45, &b0123);

        if (operand == 0b00110110) // LD (IX+d),n
        {
            d = this->ram->read(++PC);
            n = this->ram->read(++PC);
            this->ram->write(IX+d, n);
        }
        else if(operand == 0b00100001) // LD IX, nn
        {
            nn = this->getWordWithPC();
            this->IX = nn;
        }
        else if(operand == 0b00101010) // LD IX,(nn)
        {
            nn = this->getWordWithPC();
            result = this->ram->readWord(nn);
            this->IX = result;
        }
        else if(operand == 0b00100010) // LD (nn),IX
        {
            nn = this->getWordWithPC();
            this->ram->writeWord(nn, this->getIX());
        }
        else if (b67 == 0b01 && b345 == 0b110 && b012 != 0b110) // LD (IX+d),r
        {
            d = this->ram->read(++PC);
            this->ram->write(IX+d, this->regs[b012]);
        }
        else if(b67 == 0b01 && b345 != 0b110 && b012 == 0b110) // LD r,(IX+d)
        {
            d = this->ram->read(++PC);
            this->regs[b345] = this->ram->read(IX+d);
        }
    }
    else if(opcode == 0b11111111) // LD r,(IY+d)
    {
        reg = this->getMostSignificantRegister(this->ram->read(++PC));
        d = this->ram->read(++PC);
        this->regs[reg] = this->ram->read(IY+d);
    }
    else if(opcode == 0b11111101)
    {
        operand = this->ram->read(++PC);
        // Bit split the óperand
        b_split(operand, &b67, &b345, &b012, &b45, &b0123);

        if (operand == 0b00110110) // LD (IY+d), n
        {
            d = this->ram->read(++PC);
            n = this->ram->read(++PC);
            this->ram->write(IY+d, n);
        }
        else if(operand == 0b00100001) // LD IY, nn
        {
            nn = this->getWordWithPC();
            this->IY = nn;
        }
        else if(operand == 0b00101010) // LD IY,(nn)
        {
            nn = this->getWordWithPC();
            this->IY = this->ram->readWord(nn);
        }
        else if(b67 == 0b01 && b345 == 0b110 && b0123 != 0b110)// LD (IY+d),r
        {
            d = this->ram->read(++PC);
            reg = this->getLeastSignificantRegister(operand);
            this->ram->write(IY+d, this->regs[reg]);
        }
    }
    else if(opcode == 0b00110110) // LD(HL),n
    {
        n = this->ram->read(++PC);
        this->ram->write(this->getHL(), n);
    }
    else if(b67 == 0b01 && b345 == 0b110 && b012 != 0b110) // LD (HL), r
    {
        this->ram->write(this->getHL(), this->regs[b012]);
    }
    else if(opcode == 0b00001010) // LD A,(BC)
    {
        this->regs[A_REG] = this->ram->read(this->getBC());
    }
    else if(opcode == 0b00011010) // LD A,(DE)
    {
        this->regs[A_REG] = this->ram->read(this->getDE());
    }
    else if(opcode == 0b00111010) // LD A,(nn)
    {
        nn = this->getWordWithPC();
        this->regs[A_REG] = this->ram->read(nn);
    }
    else if(opcode == 0b00000010) // LD (BC),A
    {
        this->ram->write(this->getBC(), this->regs[A_REG]);
    }
    else if(opcode == 0b00010010) // LD (DE),A
    {
        this->ram->write(this->getDE(), this->regs[A_REG]);
    }
    else if(opcode == 0b00110010) // LD (nn),A
    {
        nn = this->getWordWithPC();
        this->ram->write(nn, this->regs[A_REG]);
    }
    else if (opcode == 0b11101101)
    {
        operand = this->ram->read(++PC);
        // Bit split the óperand
        b_split(operand, &b67, &b345, &b012, &b45, &b0123);
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
        else if(b67 == 0b01 && b0123 == 0b1011) // LD dd,(nn)
        {
            nn = this->getWordWithPC();
            result = this->ram->readWord(nn);
            this->setRegPair(b45, result);
        }
        else if(b67 == 0b01 && b0123 == 0b0011) // LD (nn),dd
        {
            nn = this->getWordWithPC();
            this->ram->writeWord(nn, this->getRegPair(b45));
        }
    }
    else if(b67 == 0b00 && b0123 == 0b0001) // LD dd,nn
    {
        nn = this->getWordWithPC();
        this->setRegPair(b45, nn);
    }
    else if(opcode == 0b00101010) // LD HL,(nn)
    {
        nn = this->getWordWithPC();
        this->regs[L_REG] = this->ram->read(nn);
        this->regs[H_REG] = this->ram->read(nn+1);
    }
    else if(opcode == 0b00100010) // LD (nn),HL
    {
        nn = this->getWordWithPC();
        this->ram->writeWord(nn, this->getRegPair(HL_REG_PAIR));
    }

    // Last instruction LD (nn),IX
    else
    {
        std::cout << "Bad Opcode: "  << (int) opcode << std::endl;
    }

    R++;
}
