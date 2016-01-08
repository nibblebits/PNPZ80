/* This source file is protected under the GPL License V3. Please view the file
   called "COPYING" to view the license with your rights for this source file and the rest of the PNPZ80 project.
   If the license in the file "COPYING" was not included in this distribution you may find it here: http://www.gnu.org/licenses/gpl.txt*/

#ifndef PNPZ80AUDIO_H
#define PNPZ80AUDIO_H
#include <PNPZ80Hardware.h>
class PNPZ80Audio : public PNPZ80Hardware
{
    public:
        PNPZ80Audio();
        virtual ~PNPZ80Audio();

        bool init();
        void reset();
        bool process();
        void input(uint8_t addr, uint8_t value);
    protected:
    private:
};

#endif // PNPZ80AUDIO_H
