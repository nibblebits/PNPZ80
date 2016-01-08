/* This source file is protected under the GPL License V3. Please view the file
   called "COPYING" to view the license with your rights for this source file and the rest of the PNPZ80 project.
   If the license in the file "COPYING" was not included in this distribution you may find it here: http://www.gnu.org/licenses/gpl.txt*/
#ifndef PNPZ80HARDWARE_H
#define PNPZ80HARDWARE_H

#include "PNPZ80.h"
#include "PNPZ80Instance.h"
#include <string>
class DLL_EXPORT PNPZ80Hardware
{
    public:
        PNPZ80Hardware(std::string name, std::string version);
        virtual ~PNPZ80Hardware();
        virtual bool init() = 0;
        virtual void reset() = 0;
        virtual bool process() = 0;
        virtual void input(uint8_t addr, uint8_t value) {};
        virtual void output(uint8_t addr, uint8_t* value) {};
        bool registerIOAddress(uint8_t addr);
        void setPNPZ80Instance(PNPZ80Instance* inst);
        PNPZ80Instance* getPNPZ80Instance();
        std::string getName();
        std::string getVersion();
    protected:
    private:
        std::string name;
        std::string version;
        PNPZ80Instance* instance;
};

#endif // PNPZ80HARDWARE_H
