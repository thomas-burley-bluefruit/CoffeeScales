#pragma once

#include "DisplayJustify.h"
#include "gfx.h"

namespace coffeescales::display
{

static constexpr gJustify UgfxJustify(Justify justify)
{
    switch (justify)
    {
        case Justify::Left:
            return gJustify::gJustifyLeft;
        case Justify::Center:
            return gJustify::gJustifyCenter;
        case Justify::Right:
            return gJustify::gJustifyRight;
        case Justify::Top:
            return gJustify::gJustifyTop;
        case Justify::Middle:
            return gJustify::gJustifyMiddle;
        case Justify::Bottom:
            return gJustify::gJustifyBottom;
    }
}


}