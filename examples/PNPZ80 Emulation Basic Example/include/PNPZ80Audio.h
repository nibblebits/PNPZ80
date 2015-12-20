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
