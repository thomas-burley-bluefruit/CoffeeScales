#pragma once

#include <array>

#include "AdcDriverInterface.h"
#include "ScalesTerminalCommands.h"
#include "ScalesInterface.h"
#include "TerminalCallbackInterface.h"
#include "Terminal.h"
#include "SystemInterface.h"

namespace coffeescales::weight
{

class Scales : public coffeescales::weight::ScalesInterface,
               public terminal::TerminalCallbackInterface
{
public:
    Scales(drivers::AdcDriverInterface &adc, halwrapper::SystemInterface &system,
           terminal::TerminalInterface &terminal);
    void Task();

    // ScalesInterface
    void StartTare() override;
    bool RegisterCallback(WeightReadingCallbackInterface *callback) override;

    // TerminalCallbackInterface
    bool TerminalCommand(terminal::CommandArgs &args) override;

    [[nodiscard]] const char *CommandName() const override
    { return ScalesTerminalCommands::CommandName; }

    enum class State
    {
        Idle,
        Weigh,
        Tare,
        CalibrateStart,
        CalibrateWait,
        CalibrateSet
    };

private:
    bool ReadAdc();
    void ConvertWeight();
    void UpdateSubscribers();
    void CalibrateStart();
    void CalibrateSet();
    void PrintAdcValue();
    void PrintWeightValue();
    void Weigh();
    void Tare();

    const drivers::AdcDriverInterface &mAdc;
    const halwrapper::SystemInterface &mSystem;
    terminal::TerminalInterface &mTerminal;

    static constexpr uint32_t LoadCellRangeMg = 1'000'000;
    static constexpr uint32_t AdcReadIntervalMs = 100;


    uint32_t mLastReadTick = 0;
    int32_t mLastWeightConversionMg = 0.0f;
    int32_t mLastAdcReading = 0;
    int32_t mTareAdcReading = 0;

    int32_t mAverageSum = 0;
    size_t mAverageCount = 0;

    bool mCalibrationStartRequested = false;

    char mPrintBuffer[coffeescales::terminal::Terminal::TerminalBufferSize];
    bool mAdcDebugPrint = false;
    bool mWeightDebugPrint = false;

protected:
    State mState = State::Idle;
    static constexpr size_t MaxCallbacks = 32;
    static constexpr double CalibrationWeightMg = 100000.0;
    static constexpr size_t AveragingCount = 10;
    uint32_t mCallbackCount = 0;
    std::array<WeightReadingCallbackInterface *, MaxCallbacks> mCallbacks;
    double mCalibrationFactor;
};

}
