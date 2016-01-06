/* This source file is protected under the GPL License V3. Please view the file
   called "COPYING" to view the license with your rights for this source file and the rest of the PNPZ80 project.
   If the license in the file "COPYING" was not included in this distribution you may find it here: http://www.gnu.org/licenses/gpl.txt*/
#include "PNPZ80Audio.h"
#include <iostream>
PNPZ80Audio::PNPZ80Audio() : PNPZ80Hardware("PNPZ80Audio", "v1.0")
{
    //ctor
    PNPZ80Hardware::getPNPZ80Instance();
}

PNPZ80Audio::~PNPZ80Audio()
{
    //dtor
}

bool PNPZ80Audio::init()
{
    // We are using IO address 0x01
    if(PNPZ80Hardware::registerIOAddress(0x01))
    {
        // Return true on succession
        return true;
    }
    return false;
}
void PNPZ80Audio::reset()
{

}
bool PNPZ80Audio::process()
{
    // Return true on succession
    return true;
}

void PNPZ80Audio::input(uint8_t addr, uint8_t value)
{

}
