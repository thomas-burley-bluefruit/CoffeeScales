#include "PourRate.h"

#include <cmath>

using namespace ::coffeescales::weight;

PourRate::PourRate(ScalesInterface& scales, halwrapper::TimeInterface& time,
    drivers::ButtonDriverInterface& tareButton) :
    mTime(time)
{
    scales.RegisterCallback(this);
    tareButton.RegisterCallback(this);
}

void PourRate::RegisterCallback(PourRateUpdateCallbackInterface* callback)
{
    mCallback = callback;
}

void PourRate::NewWeightReadingMg(int32_t weightMg)
{
    const float pourRate = FilterPourRate(CalculatePourRate(weightMg));
    mLastPourRateCalculatedGramsPerSec = pourRate;
    mLastWeightReadingMg = weightMg;
    mLastWeightReadingTickMs = mTime.GetTick();

    const float pourRateRounded = std::round(pourRate * 10) / 10.0f;
    if (pourRateRounded != mLastPourRateIssuedGramsPerSec && mCallback != nullptr)
    {
        mCallback->PourRateUpdate(pourRateRounded);
        mLastPourRateIssuedGramsPerSec = pourRateRounded;
    }
}

float PourRate::CalculatePourRate(int32_t newReadingMg)
{
    if (newReadingMg < mLastWeightReadingMg)
    {
        mLastPourRateCalculatedGramsPerSec = 0;
        return 0;
    }

    const auto timeNowMs = mTime.GetTick();
    const float timeDifferenceSecs = (timeNowMs - mLastWeightReadingTickMs) / 1000.0f;

    const float weightDifferenceG = (newReadingMg - mLastWeightReadingMg) / 1000.0f;

    return weightDifferenceG / timeDifferenceSecs;
}

float PourRate::FilterPourRate(float gramsPerSec)
{
    return FilterTimeConstant * static_cast<float>(mLastPourRateCalculatedGramsPerSec)
        + (1.0f - FilterTimeConstant) * gramsPerSec;
}

void PourRate::OnButtonPress(const drivers::buttons::Button button, const uint32_t tickMs)
{
    mLastWeightReadingMg = 0;
}