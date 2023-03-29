#include "GenericTerminalCommands.h"
#include "Scales.h"
#include "ScalesTerminalMessages.h"

#include <cstring>
#include <string>

using namespace ::coffeescales::drivers;
using namespace ::coffeescales::halwrapper;
using namespace ::coffeescales::terminal;
using namespace ::coffeescales::weight;

Scales::Scales(AdcDriverInterface &adc, SystemInterface &system, TerminalInterface &terminal,
               ScalesMemoryItemInterface &memory) :
        mAdc(adc), mSystem(system),
        mTerminal(terminal),
        mMemory(memory)
{
    mCallbacks.fill(nullptr);
    memset(mPrintBuffer, 0, Terminal::TerminalBufferSize);
}

void Scales::Init()
{
    mCalibrationFactor = mMemory.GetCalibrationFactor();
    TareInit();
}

void Scales::Task()
{
    bool readSuccess = ReadAdc();

    switch (mState)
    {
        case State::Weigh:
            if (readSuccess)
                StateWeigh();
            break;

        case State::Tare:
            if (readSuccess)
                StateTare();
            break;

        case State::CalibrateStart:
            StateCalibrateStart();
            break;

        case State::CalibrateSet:
            if (readSuccess)
                StateCalibrateSet();
            break;

        case State::CalibrateWait:
        case State::Idle:
        default:
            break;
    }
}

void Scales::StateWeigh()
{
    ConvertWeight();
    UpdateSubscribers();
    if (mWeightDebugPrint)
        PrintWeightValue();
}

void Scales::StateTare()
{
    mAverageSum += mLastAdcReading;
    mAverageCount++;

    if (mAverageCount >= AveragingCount)
    {
        mTareAdcReading = mAverageSum / static_cast<int32_t>(AveragingCount);
        ConvertWeight();
        UpdateSubscribers();

        if (mCalibrationStartRequested)
            mState = State::CalibrateStart;
        else
            mState = State::Weigh;
    }
}

void Scales::StateCalibrateStart()
{
    mTerminal.TextOut(ScalesTerminalMessages::CalibratePlaceWeight);
    mCalibrationStartRequested = false;
    mAverageCount = 0;
    mAverageSum = 0;
    mState = State::CalibrateWait;
}

void Scales::StateCalibrateSet()
{
    mAverageSum += mLastAdcReading;
    mAverageCount++;

    if (mAverageCount >= AveragingCount)
    {
        const int32_t averageReading = mAverageSum / static_cast<int32_t>(mAverageCount);
        mCalibrationFactor = (averageReading - mTareAdcReading) / CalibrationWeightMg;
        mMemory.SetCalibrationFactor(mCalibrationFactor);
        mTerminal.TextOut(ScalesTerminalMessages::CalibrateComplete);
        mState = State::Weigh;
    }
}

bool Scales::ReadAdc()
{
    bool readSuccess = false;
    const auto tick = mSystem.GetTick();

    if (tick - mLastReadTick >= AdcReadIntervalMs)
        readSuccess = mAdc.Read(mLastAdcReading);

    if (readSuccess)
    {
        mLastReadTick = tick;
        if (mAdcDebugPrint)
            PrintAdcValue();
    }

    return readSuccess;
}

void Scales::ConvertWeight()
{
    const auto adcReadingDelta = mLastAdcReading - mTareAdcReading;
    mLastWeightConversionMg = static_cast<int32_t>(adcReadingDelta / mCalibrationFactor);
}

void Scales::UpdateSubscribers()
{
    for (size_t i = 0; i < mCallbackCount; ++i)
    {
        if (mCallbacks[i] == nullptr)
            continue;
        mCallbacks[i]->NewWeightReadingMg(mLastWeightConversionMg);
    }
}

void Scales::PrintAdcValue()
{
    snprintf(mPrintBuffer, Terminal::TerminalBufferSize, ScalesTerminalMessages::AdcPrintFormat,
             mLastAdcReading);
    mTerminal.TextOut(mPrintBuffer);
}

void Scales::PrintWeightValue()
{
    snprintf(mPrintBuffer, Terminal::TerminalBufferSize, ScalesTerminalMessages::WeightPrintFormat,
             mLastWeightConversionMg);
    mTerminal.TextOut(mPrintBuffer);
}

void Scales::TareInit()
{
    mState = State::Tare;
    mAverageSum = 0;
    mAverageCount = 0;
}

bool Scales::RegisterCallback(WeightReadingCallbackInterface *callback)
{
    if (mCallbackCount >= MaxCallbacks)
        return false;

    mCallbacks[mCallbackCount++] = callback;
    return true;
}

void Scales::CalibrateInit()
{
    TareInit();
    mCalibrationStartRequested = true;
}

void Scales::CalibrateSet()
{
    if (mState != State::CalibrateWait)
        return;

    mState = State::CalibrateSet;
}

void Scales::AdcDebugPrint(bool on)
{
    mAdcDebugPrint = on;
}

void Scales::WeightDebugPrint(bool on)
{
    mWeightDebugPrint = on;
}
