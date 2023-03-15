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
    CheckWeight();
    if (mCalibrationStartRequested)
        StartCalibration();
    if (mCalibrationSetRequested)
        SetCalibration();
}

void Scales::Tare()
{
    mTaring = true;
    mTareAverageSum = 0;
    mTareAverageCount = 0;
}

void Scales::TareTask()
{
    mTareAverageSum += mLastAdcReading;
    mTareAverageCount++;

    if (mTareAverageCount >= AveragingCount)
    {
        mTareAdcReading = mTareAverageSum / AveragingCount;
        ConvertWeight();
        UpdateSubscribers();
        mTaring = false;
    }
}

void Scales::CheckWeight()
{
    bool readSuccess = false;
    const auto tick = mSystem.GetTick();

    if (tick - mLastReadTick >= AdcReadIntervalMs)
    {
        readSuccess = mAdc.Read(mLastAdcReading);
        mLastReadTick = tick;
    }

    if (!readSuccess)
        return;

    ConvertWeight();
    UpdateSubscribers();

    if (mTaring)
        TareTask();

    if (mAdcDebugPrint)
        PrintAdcValue();
    if (mWeightDebugPrint)
        PrintWeightValue();
}

void Scales::ConvertWeight()
{
    const auto taredAdcReading = mLastAdcReading - mTareAdcReading;
    mLastWeightConversionMg = taredAdcReading / mCalibrationFactor;
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

void Scales::StartCalibration()
{
    Tare();
    mTerminal.TextOut(ScalesTerminalMessages::CalibratePlaceWeight);
    mCalibrationStartRequested = false;
    mCalibrationStarted = true;
}

void Scales::SetCalibration()
{
    mCalibrationFactor = (mLastAdcReading - mTareAdcReading) / CalibrationWeightMg;
    mCalibrationSetRequested = false;
    mCalibrationStarted = false;
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
            mCalibrationStartRequested = true;
            return true;
        }

        if (args.Count == 2 && args.Arg1Is(ScalesTerminalCommands::Set) &&
            mCalibrationStarted)
        {
            mCalibrationSetRequested = true;
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

    return false;
}
