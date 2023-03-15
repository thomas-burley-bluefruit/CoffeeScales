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
    void Tare() override;
    bool RegisterCallback(WeightReadingCallbackInterface *callback) override;

    // TerminalCallbackInterface
    bool TerminalCommand(terminal::CommandArgs &args) override;

    const char *CommandName() const override
    { return ScalesTerminalCommands::CommandName; }

private:
    void CheckWeight();
    void ConvertWeight();
    void UpdateSubscribers();
    void StartCalibration();
    void SetCalibration();
    void PrintAdcValue();
    void PrintWeightValue();
    void TareTask();

    const drivers::AdcDriverInterface &mAdc;
    const halwrapper::SystemInterface &mSystem;
    terminal::TerminalInterface &mTerminal;

    static constexpr uint32_t LoadCellRangeMg = 1'000'000;
    static constexpr uint32_t AdcReadIntervalMs = 100;

    uint32_t mLastReadTick = 0;
    int32_t mLastWeightConversionMg = 0.0f;
    int32_t mLastAdcReading = 0;

    bool mTaring = false;
    int32_t mTareAverageSum = 0;
    size_t mTareAverageCount = 0;
    int32_t mTareAdcReading = 0;

    bool mCalibrationStartRequested = false;
    bool mCalibrationStarted = false;
    bool mCalibrationSetRequested = false;

    char mPrintBuffer[coffeescales::terminal::Terminal::TerminalBufferSize];
    bool mAdcDebugPrint = false;
    bool mWeightDebugPrint = false;

protected:
    static constexpr size_t MaxCallbacks = 32;
    static constexpr double CalibrationWeightMg = 100000.0;
    static constexpr size_t AveragingCount = 10;
    uint32_t mCallbackCount = 0;
    std::array<WeightReadingCallbackInterface *, MaxCallbacks> mCallbacks;
    double mCalibrationFactor;
};

}
