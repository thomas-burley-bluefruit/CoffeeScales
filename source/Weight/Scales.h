#pragma once

#include <array>

#include "AdcDriverInterface.h"
#include "ButtonDriverInterface.h"
#include "ButtonPressCallbackInterface.h"
#include "ScalesInterface.h"
#include "ScalesMemoryItem.h"
#include "ScalesTerminalCommands.h"
#include "SystemInterface.h"
#include "Terminal.h"
#include "TerminalCallbackInterface.h"

namespace coffeescales::weight
{

class Scales
        : public coffeescales::weight::ScalesInterface, public drivers::ButtonPressCallbackInterface
{
public:
    Scales(drivers::AdcDriverInterface &adc, halwrapper::SystemInterface &system,
           terminal::TerminalInterface &terminal, ScalesMemoryItemInterface &memory,
           drivers::ButtonDriverInterface &tareButton);

    void Init();
    void Task();

    // ScalesInterface
    void TareInit() override;
    bool RegisterCallback(WeightReadingCallbackInterface *callback) override;
    void CalibrateInit() override;
    void CalibrateSet() override;
    void AdcDebugPrint(bool on) override;
    void WeightDebugPrint(bool on) override;
    void OnButtonPress(drivers::buttons::Button button) override;

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
    void StateWeigh();
    void StateTare();
    void StateCalibrateStart();
    void StateCalibrateSet();

    bool ReadAdc();
    void ConvertWeight();
    void UpdateSubscribers();
    void PrintAdcValue();
    void PrintWeightValue();
    void FilterWeight(float newReadingMg);

protected:
    State mState = State::Idle;
    static constexpr size_t MaxCallbacks = 32;
    static constexpr double CalibrationWeightMg = 200000.0;
    static constexpr size_t AveragingCount = 10;
    uint32_t mCallbackCount = 0;
    std::array<WeightReadingCallbackInterface *, MaxCallbacks> mCallbacks;
    float mCalibrationFactor;

private:
    const drivers::AdcDriverInterface &mAdc;
    const halwrapper::SystemInterface &mSystem;
    terminal::TerminalInterface &mTerminal;
    ScalesMemoryItemInterface &mMemory;
    drivers::ButtonDriverInterface &mTareButton;

    static constexpr uint32_t AdcReadIntervalMs = 100;
    static constexpr float FilterTimeConstant = 0.1f;

    uint32_t mLastReadTick = 0;
    int32_t mLastWeightConversionMg = 0.0f;
    int32_t mLastAdcReading = 0;
    int32_t mTareAdcReading = 0;

    int32_t mAverageSum = 0;
    size_t mAverageCount = 0;

    bool mCalibrationStartRequested = false;
    bool mTareInitRequested = false;

    char mPrintBuffer[coffeescales::terminal::Terminal::TerminalBufferSize];
    bool mAdcDebugPrint = false;
    bool mWeightDebugPrint = false;
};

}
