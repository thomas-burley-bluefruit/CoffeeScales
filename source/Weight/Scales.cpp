#include "GenericTerminalCommands.h"
#include "Scales.h"
#include "ScalesTerminalMessages.h"

#include <cstring>
#include <string>

using namespace ::coffeescales::drivers;
using namespace ::coffeescales::halwrapper;
using namespace ::coffeescales::terminal;
using namespace ::coffeescales::weight;

Scales::Scales(AdcDriverInterface &adc, SystemInterface &system, TerminalInterface &terminal) :
        mAdc(adc), mSystem(system),
        mTerminal(terminal),
        mCalibrationFactor(static_cast<double>(mAdc.MaxValue()) / LoadCellRangeMg)
{
    mCallbacks.fill(nullptr);
    memset(mPrintBuffer, 0, Terminal::TerminalBufferSize);
    mTerminal.RegisterCommandHandler(this);
}

void Scales::Task()
{
    bool readSuccess = ReadAdc();

    switch (mState)
    {
        case State::Weigh:
            if (readSuccess)
                Weigh();
            break;

        case State::Tare:
            if (readSuccess)
                Tare();
            break;

        case State::CalibrateStart:
            CalibrateStart();
            break;

        case State::CalibrateSet:
            if (readSuccess)
                CalibrateSet();
            break;

        case State::CalibrateWait:
        case State::Idle:
        default:
            break;
    }
}

void Scales::StartTare()
{
    mState = State::Tare;
    mAverageSum = 0;
    mAverageCount = 0;
}

void Scales::Weigh()
{
    ConvertWeight();
    UpdateSubscribers();
    if (mWeightDebugPrint)
        PrintWeightValue();
}

void Scales::Tare()
{
    mAverageSum += mLastAdcReading;
    mAverageCount++;

    if (mAverageCount >= AveragingCount)
    {
        mTareAdcReading = mAverageSum / AveragingCount;
        ConvertWeight();
        UpdateSubscribers();

        if (mCalibrationStartRequested)
            mState = State::CalibrateStart;
        else
            mState = State::Weigh;
    }
}

void Scales::CalibrateStart()
{
    mTerminal.TextOut(ScalesTerminalMessages::CalibratePlaceWeight);
    mCalibrationStartRequested = false;
    mAverageCount = 0;
    mAverageSum = 0;
    mState = State::CalibrateWait;
}

void Scales::CalibrateSet()
{
    mAverageSum += mLastAdcReading;
    mAverageCount++;

    if (mAverageCount >= AveragingCount)
    {
        const int32_t averageReading = mAverageSum / mAverageCount;
        mCalibrationFactor = (averageReading - mTareAdcReading) / CalibrationWeightMg;
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
    mLastWeightConversionMg = adcReadingDelta / mCalibrationFactor;
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

bool Scales::RegisterCallback(WeightReadingCallbackInterface *callback)
{
    if (mCallbackCount >= MaxCallbacks)
        return false;

    mCallbacks[mCallbackCount++] = callback;
    return true;
}

bool Scales::TerminalCommand(CommandArgs &args)
{
    if (args.Arg0Is(ScalesTerminalCommands::Calibrate))
    {
        if (args.Count == 1)
        {
            StartTare();
            mCalibrationStartRequested = true;
            return true;
        }

        if (args.Count == 2 && args.Arg1Is(ScalesTerminalCommands::Set) &&
            mState == State::CalibrateWait)
        {
            mState = State::CalibrateSet;
            return true;
        }
    }

    if (args.Arg0Is(ScalesTerminalCommands::Adc))
    {
        if (args.Count != 2)
            return false;

        if (args.Arg1Is(GenericTerminalCommands::On))
        {
            mAdcDebugPrint = true;
            return true;
        }

        if (args.Arg1Is(GenericTerminalCommands::Off))
        {
            mAdcDebugPrint = false;
            return true;
        }
    }

    if (args.Arg0Is(ScalesTerminalCommands::Weight))
    {
        if (args.Count != 2)
            return false;

        if (args.Arg1Is(GenericTerminalCommands::On))
        {
            mWeightDebugPrint = true;
            return true;
        }

        if (args.Arg1Is(GenericTerminalCommands::Off))
        {
            mWeightDebugPrint = false;
            return true;
        }
    }

    if (args.Count == 1 && args.Arg0Is(ScalesTerminalCommands::Tare))
    {
        StartTare();
        return true;
    }

    return false;
}
