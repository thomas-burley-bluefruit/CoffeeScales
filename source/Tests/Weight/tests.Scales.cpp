#include "gtest/gtest.h"

#include "AdcSpy.h"
#include "GenericTerminalCommands.h"
#include "Scales.cpp"
#include "ScalesTerminalMessages.h"
#include "Terminal.h"
#include "TerminalSpy.h"
#include "SystemMock.h"
#include "WeightReadingCallbackSpy.h"

#include <string>
#include <vector>

using namespace ::coffeescales::halwrapper;
using namespace ::coffeescales::drivers;
using namespace ::coffeescales::terminal;

using std::vector;

class ScalesTestObject : public Scales
{
public:
    ScalesTestObject(AdcDriverInterface &adc, SystemInterface &system, TerminalInterface &terminal)
            : Scales(adc, system, terminal)
    {}

    static constexpr size_t MaxCallbacks = Scales::MaxCallbacks;
    static constexpr size_t AveragingCoung = Scales::AveragingCount;
    std::array<WeightReadingCallbackInterface *, MaxCallbacks> &Callbacks = mCallbacks;
    uint32_t &CallbackCount = mCallbackCount;
    double &CalibrationFactor = mCalibrationFactor;
    static constexpr double CalibrationWeight = Scales::CalibrationWeightMg;
};

class ScalesTests : public testing::Test
{
public:
    ScalesTests() : mScales(mAdc, mSystem, mTerminal)
    {}

    void TriggerAdcRead()
    {
        mSystem.SysTick += 100;
        mScales.Task();
    }

    void SetCommandArg(CommandArgs& args, size_t index, const char* arg)
    {
        if (index > CommandArgs::MaxArguments - 1)
            return;

        strncpy_s(args.Arguments[index].data(), CommandArgs::MaxArgLength,
                  arg, CommandArgs::MaxArgLength);
    }

    WeightReadingCallbackSpy mCallback;
    AdcSpy mAdc;
    TerminalSpy mTerminal;
    SystemMock mSystem;
    ScalesTestObject mScales;
};

TEST_F(ScalesTests, Can_register_callback)
{
    ASSERT_TRUE(mScales.RegisterCallback(&mCallback));
    ASSERT_EQ(mScales.CallbackCount, 1);
    ASSERT_EQ(mScales.Callbacks[0], &mCallback);
}

TEST_F(ScalesTests, Can_only_register_up_to_max_callbacks)
{
    // Given, when
    for (size_t i = 0; i < mScales.MaxCallbacks; ++i)
        ASSERT_TRUE(mScales.RegisterCallback(&mCallback));

    // Then
    ASSERT_EQ(mScales.CallbackCount, mScales.MaxCallbacks);
    ASSERT_FALSE(mScales.RegisterCallback(&mCallback));
}

TEST_F(ScalesTests, Task_reads_ADC_every_100ms)
{
    // Given
    mScales.Task();
    ASSERT_EQ(mAdc.ReadCallCount, 0);
    mSystem.SysTick = 99;
    mScales.Task();
    ASSERT_EQ(mAdc.ReadCallCount, 0);

    // When
    mSystem.SysTick = 100;
    mScales.Task();

    // Then
    ASSERT_EQ(mAdc.ReadCallCount, 1);

    // When
    mSystem.SysTick += 101; // may not be called on exactly hundredth subsequent tick
    mScales.Task();

    // Then
    ASSERT_EQ(mAdc.ReadCallCount, 2);
}

TEST_F(ScalesTests, Task_handles_systick_overflow)
{
    // Given
    mScales.Task();
    ASSERT_EQ(mAdc.ReadCallCount, 0);

    mSystem.SysTick = INT32_MAX;
    mScales.Task();

    ASSERT_EQ(mAdc.ReadCallCount, 1);

    // When
    mSystem.SysTick += 99;
    mScales.Task();

    // Then
    ASSERT_EQ(mAdc.ReadCallCount, 1);

    // When
    mSystem.SysTick += 1;
    mScales.Task();

    // Then
    ASSERT_EQ(mAdc.ReadCallCount, 2);
}

TEST_F(ScalesTests, Task_calls_registered_callback_after_successful_ADC_read)
{
    // Given
    ASSERT_TRUE(mScales.RegisterCallback(&mCallback));
    mAdc.ReadSuccess = true;

    // When
    TriggerAdcRead();

    // Then
    ASSERT_EQ(1, mCallback.CallCount);
}

TEST_F(ScalesTests, Task_does_not_call_registered_callback_after_unsuccessful_ADC_read)
{
    // Given
    ASSERT_TRUE(mScales.RegisterCallback(&mCallback));
    mAdc.ReadSuccess = false;

    // When
    TriggerAdcRead();

    // Then
    ASSERT_EQ(0, mCallback.CallCount);
}

TEST_F(ScalesTests, Task_calls_all_registered_callbacks_after_successful_ADC_read)
{
    // Given
    std::vector<WeightReadingCallbackSpy> callbacks(5, WeightReadingCallbackSpy());
    for (auto &callback: callbacks)
        ASSERT_TRUE(mScales.RegisterCallback(&callback));

    mAdc.ReadSuccess = true;

    // When
    TriggerAdcRead();

    // Then
    for (auto &callback: callbacks)
        ASSERT_EQ(1, callback.CallCount);
}

TEST_F(ScalesTests, Adc_readings_are_scaled_by_calibration_factor_when_passed_to_callback)
{
    // Given
    mScales.RegisterCallback(&mCallback);

    const int32_t adcValue = 1'000'000;
    mAdc.ReadValue = adcValue;
    const int32_t expectedWeight = adcValue / mScales.CalibrationFactor;

    // When
    TriggerAdcRead();

    // Then
    ASSERT_EQ(1, mCallback.CallCount);
    ASSERT_EQ(expectedWeight, mCallback.LastWeightReading);
}

TEST_F(ScalesTests, Tare_sets_tare_point_as_average_of_next_n_readings)
{
    // Given
    mScales.RegisterCallback(&mCallback);

    vector<int32_t> tareAdcReadings = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    int32_t averageTareAdcReading = 0;
    for (auto reading : tareAdcReadings)
        averageTareAdcReading += reading;
    averageTareAdcReading = static_cast<int32_t>(averageTareAdcReading / tareAdcReadings.size());

    // When: tared
    mScales.Tare();
    for (auto reading : tareAdcReadings)
    {
        mAdc.ReadValue = reading;
        TriggerAdcRead();
    }

    mAdc.ReadValue = averageTareAdcReading;
    TriggerAdcRead();
    ASSERT_EQ(0, mCallback.LastWeightReading);

    // When: ADC value subsequently increases
    const int32_t additionalAdcValue = 333'300;
    mAdc.ReadValue += additionalAdcValue;
    TriggerAdcRead();

    const int32_t expectedWeight = additionalAdcValue / mScales.CalibrationFactor;
    ASSERT_EQ(expectedWeight, mCallback.LastWeightReading);
}

TEST_F(ScalesTests, task_after_calibrate_terminal_command_performs_tare)
{
    // Given
    mScales.RegisterCallback(&mCallback);

    CommandArgs args;
    strncpy_s(args.Arguments[0].data(), CommandArgs::MaxArgLength,
              "calibrate", CommandArgs::MaxArgLength);
    args.Count++;

    // When
    ASSERT_TRUE(mScales.TerminalCommand(args));
    mScales.Task();

    // Then
    ASSERT_EQ(mCallback.CallCount, 1);
    ASSERT_EQ(mCallback.LastWeightReading, 0);
}

TEST_F(ScalesTests, task_after_calibrate_terminal_command_instructs_user_to_place_weight_on_scale)
{
    // Given
    CommandArgs args;
    strncpy_s(args.Arguments[0].data(), CommandArgs::MaxArgLength,
              ScalesTerminalCommands::Calibrate, CommandArgs::MaxArgLength);
    args.Count++;

    // When
    ASSERT_TRUE(mScales.TerminalCommand(args));
    mScales.Task();

    // Then
    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(mTerminal.TextOutValue, ScalesTerminalMessages::CalibratePlaceWeight);
}

TEST_F(ScalesTests, task_after_calibrate_set_terminal_command_updates_calibration_factor_if_calibration_started)
{
    // Given
    CommandArgs calibrateStartArgs;
    SetCommandArg(calibrateStartArgs, 0, ScalesTerminalCommands::Calibrate);
    calibrateStartArgs.Count++;
    ASSERT_TRUE(mScales.TerminalCommand(calibrateStartArgs));
    mScales.Task();

    CommandArgs setArgs;
    SetCommandArg(setArgs, 0, ScalesTerminalCommands::Calibrate);
    setArgs.Count++;
    SetCommandArg(setArgs, 1, ScalesTerminalCommands::Set);
    setArgs.Count++;

    const int32_t calibrationAdcValue = 50'000;
    mAdc.ReadValue = calibrationAdcValue;
    const double expectedCalibrationFactor = calibrationAdcValue / ScalesTestObject::CalibrationWeight;

    // When
    ASSERT_TRUE(mScales.TerminalCommand(setArgs));
    mSystem.SysTick += 100;
    mScales.Task();

    // Then
    ASSERT_EQ(expectedCalibrationFactor, mScales.CalibrationFactor);
}

TEST_F(ScalesTests, task_after_calibrate_set_terminal_command_does_not_update_calibration_factor_if_calibration_not_started)
{
    // Given
    const double initialCalibrationFactor = mScales.CalibrationFactor;

    CommandArgs setArgs;
    SetCommandArg(setArgs, 0, ScalesTerminalCommands::Calibrate);
    setArgs.Count++;
    SetCommandArg(setArgs, 1, ScalesTerminalCommands::Set);
    setArgs.Count++;

    const int32_t calibrationAdcValue = 50'000;
    mAdc.ReadValue = calibrationAdcValue;

    // When
    ASSERT_FALSE(mScales.TerminalCommand(setArgs));
    mSystem.SysTick += 100;
    mScales.Task();

    // Then
    ASSERT_EQ(initialCalibrationFactor, mScales.CalibrationFactor);
}

TEST_F(ScalesTests, adc_on_terminal_command_prints_adc_value_on_next_task)
{
    // Given
    CommandArgs args;
    SetCommandArg(args, 0, ScalesTerminalCommands::Adc);
    args.Count++;
    SetCommandArg(args, 1, GenericTerminalCommands::On);
    args.Count++;

    mAdc.ReadValue = 123456;

    char expectedMessage[Terminal::TerminalBufferSize];
    snprintf(expectedMessage, Terminal::TerminalBufferSize, ScalesTerminalMessages::AdcPrintFormat,
             mAdc.ReadValue);

    // When
    mScales.TerminalCommand(args);
    TriggerAdcRead();

    // Then
    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(expectedMessage, mTerminal.TextOutValue);
}

TEST_F(ScalesTests, adc_off_terminal_command_stops_printing_adc_values_on_task)
{
    // Given
    CommandArgs args;
    SetCommandArg(args, 0, ScalesTerminalCommands::Adc);
    args.Count++;
    SetCommandArg(args, 1, GenericTerminalCommands::On);
    args.Count++;

    mAdc.ReadValue = 123456;

    char expectedMessage[Terminal::TerminalBufferSize];
    snprintf(expectedMessage, Terminal::TerminalBufferSize, ScalesTerminalMessages::AdcPrintFormat,
             mAdc.ReadValue);

    mScales.TerminalCommand(args);
    TriggerAdcRead();

    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(expectedMessage, mTerminal.TextOutValue);

    // When
    mTerminal.TextOutCalled = false;
    SetCommandArg(args, 1, GenericTerminalCommands::Off);
    mScales.TerminalCommand(args);
    TriggerAdcRead();

    // Then
    ASSERT_FALSE(mTerminal.TextOutCalled);
}

TEST_F(ScalesTests, weight_on_terminal_command_prints_weight_value_on_next_task)
{
    // Given
    mScales.RegisterCallback(&mCallback);

    CommandArgs args;
    SetCommandArg(args, 0, ScalesTerminalCommands::Weight);
    args.Count++;
    SetCommandArg(args, 1, GenericTerminalCommands::On);
    args.Count++;

    mAdc.ReadValue = 123456;
    TriggerAdcRead();

    char expectedMessage[Terminal::TerminalBufferSize];
    snprintf(expectedMessage, Terminal::TerminalBufferSize, ScalesTerminalMessages::WeightPrintFormat,
             mCallback.LastWeightReading);

    // When
    mScales.TerminalCommand(args);
    TriggerAdcRead();

    // Then
    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(expectedMessage, mTerminal.TextOutValue);
}

TEST_F(ScalesTests, weight_off_terminal_command_stops_printing_weight_values_on_task)
{
    // Given
    mScales.RegisterCallback(&mCallback);

    CommandArgs args;
    SetCommandArg(args, 0, ScalesTerminalCommands::Weight);
    args.Count++;
    SetCommandArg(args, 1, GenericTerminalCommands::On);
    args.Count++;

    mAdc.ReadValue = 123456;
    TriggerAdcRead();

    char expectedMessage[Terminal::TerminalBufferSize];
    snprintf(expectedMessage, Terminal::TerminalBufferSize, ScalesTerminalMessages::WeightPrintFormat,
             mCallback.LastWeightReading);

    mScales.TerminalCommand(args);
    TriggerAdcRead();

    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(expectedMessage, mTerminal.TextOutValue);

    // When
    mTerminal.TextOutCalled = false;
    SetCommandArg(args, 1, GenericTerminalCommands::Off);
    mScales.TerminalCommand(args);
    TriggerAdcRead();

    // Then
    ASSERT_FALSE(mTerminal.TextOutCalled);
}