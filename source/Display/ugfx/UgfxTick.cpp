#include "Time.h"
#include "gfx.h"

using namespace coffeescales::halwrapper;

extern "C"
{

gTicks gfxSystemTicks()
{
    return Time::GetTickStatic();
}

gTicks gfxMillisecondsToTicks(gDelay ms)
{
    return ms;
}

}