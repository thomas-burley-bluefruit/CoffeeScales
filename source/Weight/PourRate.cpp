#include "PourRate.h"

#include <cmath>

using namespace ::coffeescales::weight;

PourRate::PourRate(ScalesInterface& scales, halwrapper::TimeInterface& time) :
    mTime(time)
{
    scales.RegisterCallback(this);
}

void PourRate::RegisterCallback(PourRateUpdateCallbackInterface* callback)
{
    mCallback = callback;
}

void PourRate::NewWeightReadingMg(int32_t weightMg)
{
    if (mCallback != nullptr && mLastWeightReadingTickMs != 0)
    {
        const auto pourRate = CalculatePourRate(weightMg);
        if (pourRate != mLastPourRateCalculated)
        {
            mCallback->PourRateUpdate(pourRate);
            mLastPourRateCalculated = pourRate;
        }
    }

    mLastWeightReadingMg = weightMg;
    mLastWeightReadingTickMs = mTime.GetTick();
}

uint32_t PourRate::CalculatePourRate(int32_t newReadingMg)
{
    if (newReadingMg < mLastWeightReadingMg)
    {
        return 0;
    }

    const auto timeNowMs = mTime.GetTick();
    const float timeDifferenceSecs = (timeNowMs - mLastWeightReadingTickMs) / 1000.0f;

    const float weightDifferenceG = (newReadingMg - mLastWeightReadingMg) / 1000.0f;

    return static_cast<uint32_t>(roundf(weightDifferenceG / timeDifferenceSecs));
}