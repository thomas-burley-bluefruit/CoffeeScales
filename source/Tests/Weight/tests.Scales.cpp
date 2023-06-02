#include "gtest/gtest.h"

#include "AdcSpy.h"
#include "ButtonDriverSpy.h"
#include "GenericTerminalCommands.h"
#include "Scales.h"
#include "ScalesMemoryItemSpy.h"
#include "ScalesTerminalMessages.h"
#include "SystemMock.h"
#include "Terminal.h"
#include "TerminalSpy.h"
#include "WeightReadingCallbackSpy.h"

#include <string>
#include <vector>

using namespace ::coffeescales::halwrapper;
using namespace ::coffeescales::drivers;
using namespace ::coffeescales::terminal;
using namespace ::coffeescales::weight;

using std::vector;

class ScalesTestObject : public Scales
{
  public:
    ScalesTestObject(AdcDriverInterface& adc, SystemInterface& system, TerminalInterface& terminal,
        ScalesMemoryItemInterface& memory, ButtonDriverInterface& tareButton) :
        Scales(adc, system, terminal, memory, tareButton)
    {
    }

    static constexpr size_t MaxCallbacks = Scales::MaxCallbacks;
    static constexpr size_t AveragingCount = Scales::AveragingCount;
    std::array<WeightReadingCallbackInterface*, MaxCallbacks>& Callbacks = mCallbacks;
    uint32_t& CallbackCount = mCallbackCount;
    float& CalibrationFactor = mCalibrationFactor;
    static constexpr float CalibrationWeight = Scales::CalibrationWeightMg;
    State& State = Scales::mState;
};

class ScalesTests : public testing::Test
{
  public:
    ScalesTests() :
        mScales(mAdc, mSystem, mTerminal, mMemory, mTareButton)
    {
    }

    void SetUp() override
    {
        mMemory.GetCalibrationFactorValue = 1.0f;
        mScales.Init();
    }

    void TriggerAdcRead()
    {
        mSystem.SysTick += 100;
        mScales.Task();
    }

    void RepeatAdcValue(int32_t adcValue, size_t count)
    {
        mAdc.ReadValue = adcValue;
        for (int i = 0; i < count; ++i)
            TriggerAdcRead();
    }

    void Tare()
    {
        mScales.TareInit();
        RepeatAdcValue(0, ScalesTestObject::AveragingCount);
    }

    void CalibrationStartSequence()
    {
        Tare();
        mScales.CalibrateInit();
        RepeatAdcValue(0, ScalesTestObject::AveragingCount);
        mScales.Task();
    }

    WeightReadingCallbackSpy mCallback;
    AdcSpy mAdc;
    TerminalSpy mTerminal;
    SystemMock mSystem;
    ScalesMemoryItemSpy mMemory;
    ButtonDriverSpy mTareButton;
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
    for (size_t i = 0; i < ScalesTestObject::MaxCallbacks; ++i)
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
    Tare();
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
    Tare();
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
    Tare();
    std::vector<WeightReadingCallbackSpy> callbacks(5, WeightReadingCallbackSpy());
    for (auto& callback : callbacks)
        ASSERT_TRUE(mScales.RegisterCallback(&callback));

    mAdc.ReadSuccess = true;

    // When
    TriggerAdcRead();

    // Then
    for (auto& callback : callbacks)
        ASSERT_EQ(1, callback.CallCount);
}

TEST_F(ScalesTests, Calibration_factor_is_restored_from_memory_on_init)
{
    // Given
    float expectedCalibrationFactor = 1.23f;
    mMemory.GetCalibrationFactorValue = expectedCalibrationFactor;

    // When
    mScales.Init();

    // Then
    ASSERT_TRUE(mMemory.GetCalibrationFactorCalled);
    ASSERT_EQ(mScales.CalibrationFactor, expectedCalibrationFactor);
}

TEST_F(ScalesTests, Adc_readings_are_scaled_by_calibration_factor_when_passed_to_callback)
{
    // Given
    Tare();
    mScales.RegisterCallback(&mCallback);

    const int32_t adcValue = 1'000'000;
    mAdc.ReadValue = adcValue;
    const auto expectedWeight = static_cast<int32_t>(adcValue / mScales.CalibrationFactor);

    // When
    RepeatAdcValue(adcValue, mScales.AveragingCount);

    // Then
    ASSERT_EQ(mScales.AveragingCount, mCallback.CallCount);
    ASSERT_EQ(expectedWeight, mCallback.LastWeightReading);
}

TEST_F(ScalesTests, TareInit_sets_weight_to_zero_while_taring)
{
    // Given
    Tare();
    mScales.RegisterCallback(&mCallback);
    RepeatAdcValue(123456, 10);
    ASSERT_NE(0, mCallback.LastWeightReading);

    // When
    mScales.TareInit();

    // Then
    ASSERT_EQ(0, mCallback.LastWeightReading);
}

TEST_F(ScalesTests, Tare_sets_tare_point_as_average_of_next_n_readings)
{
    // Given
    mScales.RegisterCallback(&mCallback);

    vector<int32_t> tareAdcReadings = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int32_t averageTareAdcReading = 0;
    for (auto reading : tareAdcReadings)
        averageTareAdcReading += reading;
    averageTareAdcReading = static_cast<int32_t>(averageTareAdcReading / tareAdcReadings.size());

    // When: tared
    mScales.TareInit();
    for (auto reading : tareAdcReadings)
    {
        mAdc.ReadValue = reading;
        TriggerAdcRead();
    }

    RepeatAdcValue(averageTareAdcReading, mScales.AveragingCount);
    ASSERT_EQ(0, mCallback.LastWeightReading);

    // When: ADC value subsequently increases
    const int32_t additionalAdcValue = 333'300;
    mAdc.ReadValue += additionalAdcValue;
    RepeatAdcValue(mAdc.ReadValue, mScales.AveragingCount);

    const auto expectedWeight =
        static_cast<int32_t>(additionalAdcValue / mScales.CalibrationFactor);
    ASSERT_EQ(expectedWeight, mCallback.LastWeightReading);
}

TEST_F(ScalesTests, task_after_CalibrateInit_command_performs_tare)
{
    // Given
    Tare();
    mScales.RegisterCallback(&mCallback);

    const int32_t adcValue = 123456;

    // When
    mScales.CalibrateInit();
    RepeatAdcValue(adcValue, ScalesTestObject::AveragingCount);
    mScales.Task();

    // Then
    ASSERT_EQ(mCallback.CallCount, 2);
    ASSERT_EQ(mCallback.LastWeightReading, 0);
}

TEST_F(ScalesTests,
       task_after_CalibrateInit_instructs_user_to_place_weight_on_scale_when_taring_complete)
{
    // Given
    Tare();

    // When
    mScales.CalibrateInit();
    for (int i = 0; i < ScalesTestObject::AveragingCount; ++i)
    {
        TriggerAdcRead();
        ASSERT_FALSE(mTerminal.TextOutCalled);
    }
    mScales.Task();

    // Then
    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(mTerminal.TextOutValue, ScalesTerminalMessages::CalibratePlaceWeight);
}

TEST_F(ScalesTests,
       task_after_CalibrateSet_updates_calibration_factor_to_average_of_next_n_reading_if_calibration_started)
{
    // Given
    CalibrationStartSequence();

    vector<int32_t> calibrateAdcReadings = {50000, 51000, 52000, 53000, 54000, 55000, 56000, 57000,
        58000, 59000};
    int32_t averageCalibrateAdcReading = 0;
    for (auto reading : calibrateAdcReadings)
        averageCalibrateAdcReading += reading;
    averageCalibrateAdcReading =
        static_cast<int32_t>(averageCalibrateAdcReading / calibrateAdcReadings.size());

    // When: n calibration readings read
    mScales.CalibrateSet();
    for (auto reading : calibrateAdcReadings)
    {
        mAdc.ReadValue = reading;
        TriggerAdcRead();
    }
    const float expectedCalibrationFactor =
        averageCalibrateAdcReading / ScalesTestObject::CalibrationWeight;

    // Then
    ASSERT_EQ(expectedCalibrationFactor, mScales.CalibrationFactor);
}

TEST_F(ScalesTests,
       new_calibration_factor_is_stored_to_memory)
{
    // Given
    CalibrationStartSequence();

    vector<int32_t> calibrateAdcReadings = {50000, 51000, 52000, 53000, 54000, 55000, 56000, 57000,
        58000, 59000};
    int32_t averageCalibrateAdcReading = 0;
    for (auto reading : calibrateAdcReadings)
        averageCalibrateAdcReading += reading;
    averageCalibrateAdcReading =
        static_cast<int32_t>(averageCalibrateAdcReading / calibrateAdcReadings.size());

    // When: n calibration readings read
    mScales.CalibrateSet();
    for (auto reading : calibrateAdcReadings)
    {
        mAdc.ReadValue = reading;
        TriggerAdcRead();
    }
    const float expectedCalibrationFactor =
        averageCalibrateAdcReading / ScalesTestObject::CalibrationWeight;

    // Then
    ASSERT_TRUE(mMemory.SetCalibrationFactorCalled);
    ASSERT_EQ(expectedCalibrationFactor, mMemory.SetCalibrationFactorValue);
}

TEST_F(ScalesTests,
       task_after_CalibrateSet_does_not_update_calibration_factor_if_calibration_not_started)
{
    // Given
    Tare();

    const auto initialCalibrationFactor = mScales.CalibrationFactor;

    vector<int32_t> calibrateAdcReadings = {50000, 51000, 52000, 53000, 54000, 55000, 56000, 57000,
        58000, 59000};
    int32_t averageCalibrateAdcReading = 0;
    for (auto reading : calibrateAdcReadings)
        averageCalibrateAdcReading += reading;

    // When: n calibration readings read
    mScales.CalibrateSet();
    for (auto reading : calibrateAdcReadings)
    {
        mAdc.ReadValue = reading;
        TriggerAdcRead();
    }

    // Then
    ASSERT_EQ(initialCalibrationFactor, mScales.CalibrationFactor);
}

TEST_F(ScalesTests, confirmation_message_printed_to_terminal_after_calibration_complete)
{
    // Given
    CalibrationStartSequence();
    mTerminal.TextOutCalled = false;

    vector<int32_t> calibrateAdcReadings = {50000, 51000, 52000, 53000, 54000, 55000, 56000, 57000,
        58000, 59000};

    // When: n calibration readings read
    mScales.CalibrateSet();
    for (auto reading : calibrateAdcReadings)
    {
        mAdc.ReadValue = reading;
        TriggerAdcRead();
    }

    // Then
    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(ScalesTerminalMessages::CalibrateComplete, mTerminal.TextOutValue);
}

TEST_F(ScalesTests, AdcDebugPrint_on_prints_adc_value_on_next_task)
{
    // Given
    mAdc.ReadValue = 123456;

    char expectedMessage[Terminal::TerminalBufferSize];
    snprintf(expectedMessage, Terminal::TerminalBufferSize, ScalesTerminalMessages::AdcPrintFormat,
        mAdc.ReadValue);

    // When
    mScales.AdcDebugPrint(true);
    TriggerAdcRead();

    // Then
    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(expectedMessage, mTerminal.TextOutValue);
}

TEST_F(ScalesTests, AdcDebugPrint_off_stops_printing_adc_values_on_task)
{
    // Given
    mAdc.ReadValue = 123456;

    char expectedMessage[Terminal::TerminalBufferSize];
    snprintf(expectedMessage, Terminal::TerminalBufferSize, ScalesTerminalMessages::AdcPrintFormat,
        mAdc.ReadValue);

    mScales.AdcDebugPrint(true);
    TriggerAdcRead();

    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(expectedMessage, mTerminal.TextOutValue);

    // When
    mTerminal.TextOutCalled = false;
    mScales.AdcDebugPrint(false);
    TriggerAdcRead();

    // Then
    ASSERT_FALSE(mTerminal.TextOutCalled);
}

TEST_F(ScalesTests, WeightDebugPrint_on_prints_weight_value_on_next_task)
{
    // Given
    Tare();
    mScales.RegisterCallback(&mCallback);

    RepeatAdcValue(123456, mScales.AveragingCount);

    char expectedMessage[Terminal::TerminalBufferSize];
    snprintf(expectedMessage, Terminal::TerminalBufferSize,
        ScalesTerminalMessages::WeightPrintFormat, mCallback.LastWeightReading);

    // When
    mScales.WeightDebugPrint(true);
    TriggerAdcRead();

    // Then
    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(expectedMessage, mTerminal.TextOutValue);
}

TEST_F(ScalesTests, WeightDebugPrint_off_stops_printing_weight_values_on_task)
{
    // Given
    Tare();
    mScales.RegisterCallback(&mCallback);

    RepeatAdcValue(123456, mScales.AveragingCount);

    char expectedMessage[Terminal::TerminalBufferSize];
    snprintf(expectedMessage, Terminal::TerminalBufferSize,
        ScalesTerminalMessages::WeightPrintFormat, mCallback.LastWeightReading);

    mScales.WeightDebugPrint(true);
    TriggerAdcRead();

    ASSERT_TRUE(mTerminal.TextOutCalled);
    ASSERT_STREQ(expectedMessage, mTerminal.TextOutValue);

    // When
    mTerminal.TextOutCalled = false;
    mScales.WeightDebugPrint(false);
    TriggerAdcRead();

    // Then
    ASSERT_FALSE(mTerminal.TextOutCalled);
}

TEST_F(ScalesTests, TareInit_starts_tare_process)
{
    // Given
    Tare();
    ASSERT_EQ(Scales::State::Weigh, mScales.State);

    // When
    mScales.TareInit();

    // Then
    ASSERT_EQ(Scales::State::Tare, mScales.State);
}

TEST_F(ScalesTests, Weight_readings_are_filtered)
{
    // Given
    Tare();
    mScales.RegisterCallback(&mCallback);

    vector<int32_t> adcReadings = {57000, 58000, 59000};
    const int32_t expectedWeight = 58833;

    // When
    for (auto reading : adcReadings)
    {
        mAdc.ReadValue = reading;
        TriggerAdcRead();
    }

    // Then
    ASSERT_EQ(expectedWeight, mCallback.LastWeightReading);
}

TEST_F(ScalesTests, Init_registers_callback_with_tare_button)
{
    ASSERT_TRUE(mTareButton.RegisterCallbackCalled);
    ASSERT_EQ(&mScales, mTareButton.Callback);
}

TEST_F(ScalesTests, OnButtonPress_with_tare_argument_inits_tare_process_on_next_task_if_current_state_is_Weigh)
{
    // Given
    Tare();
    ASSERT_EQ(Scales::State::Weigh, mScales.State);

    // When
    mScales.OnButtonPress(buttons::Button::Tare);
    ASSERT_EQ(Scales::State::Weigh, mScales.State);
    mScales.Task();

    // Then
    ASSERT_EQ(Scales::State::Tare, mScales.State);
}

TEST_F(ScalesTests, OnButtonPress_with_wrong_argument_does_not_init_tare)
{
    // Given
    Tare();
    ASSERT_EQ(Scales::State::Weigh, mScales.State);

    // When
    mScales.OnButtonPress(buttons::Button::Count);
    mScales.Task();

    // Then
    ASSERT_EQ(Scales::State::Weigh, mScales.State);
}

TEST_F(ScalesTests, OnButtonPress_with_tare_argument_does_not_init_tare_if_state_is_calibrate)
{
    // Given
    Tare();
    CalibrationStartSequence();
    ASSERT_EQ(Scales::State::CalibrateWait, mScales.State);

    // When
    mScales.OnButtonPress(buttons::Button::Tare);
    mScales.Task();

    // Then
    ASSERT_EQ(Scales::State::CalibrateWait, mScales.State);
}

TEST_F(ScalesTests, Next_task_after_tare_init_actioned_does_not_reinit)
{
    // Given
    Tare();
    ASSERT_EQ(Scales::State::Weigh, mScales.State);

    // When
    mScales.OnButtonPress(buttons::Button::Tare);
    mScales.Task();
    ASSERT_EQ(Scales::State::Tare, mScales.State);
    RepeatAdcValue(0, mScales.AveragingCount);

    // Then
    ASSERT_EQ(Scales::State::Weigh, mScales.State);
}