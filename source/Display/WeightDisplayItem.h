#pragma once

#include "DisplayInterface.h"
#include "ScalesInterface.h"
#include "WeightReadingCallbackInterface.h"

namespace coffeescales::display
{

class WeightDisplayItem : public weight::WeightReadingCallbackInterface
{
public:
    WeightDisplayItem(DisplayInterface &display, weight::ScalesInterface &scales);
    void NewWeightReadingMg(int32_t weightMg) override;

private:
    DisplayInterface &mDisplay;
};

}
