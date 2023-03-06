#include "gtest/gtest.h"
#include "HX711Driver.h"
#include "SystemMock.h"

#include <vector>

using namespace ::drivers;
using namespace ::halwrapper;
using ::std::vector;

class Hx711DriverTests : public testing::Test
{
public:
    Hx711DriverTests() : mHx711(mSystem) {}

protected:
    template<typename T>
    void AppendVector(vector<T>& v1, vector<T>& v2)
    {
        v1.insert(v1.end(), v2.begin(), v2.end());
    }


    SystemMock mSystem;
    HX711Driver mHx711;
};

TEST_F(Hx711DriverTests, Read_ADC_value_returns_false_when_data_not_available)
{
    // Given
    mSystem.DataAvailable = false;

    // When
    int32_t adcVal = 0;
    bool returnVal = mHx711.ReadAdcValue(adcVal);

    // Then
    ASSERT_FALSE(returnVal);
}

TEST_F(Hx711DriverTests, Read_ADC_value_returns_true_when_data_is_available)
{
    // Given
    mSystem.DataAvailable = true;

    // When
    int32_t adcVal = 0;
    bool returnVal = mHx711.ReadAdcValue(adcVal);

    // Then
    ASSERT_TRUE(returnVal);
}

TEST_F(Hx711DriverTests, Read_ADC_value_returns_correct_ADC_value)
{
    // Given
    mSystem.DataAvailable = true;
    mSystem.AdcValue = 123456;

    // When
    int32_t adcValue = 0;
    ASSERT_TRUE(mHx711.ReadAdcValue(adcValue));

    // Then
    ASSERT_EQ(mSystem.AdcValue, adcValue);
}

TEST_F(Hx711DriverTests, Read_ADC_sequence_when_conversion_ready)
{
    // Given
    mSystem.DataAvailable = true;

    vector<SystemInterfaceCall> singleBitSequence =
            {
                    { .method = SystemInterfaceMethod::SetPinState, .gpioState = GpioPinState::Set },
                    { .method = SystemInterfaceMethod::DelayUs, .delayUs = HX711Driver::TimingDelayUs },
                    { .method = SystemInterfaceMethod::GetPinState },
                    { .method = SystemInterfaceMethod::SetPinState, .gpioState = GpioPinState::Reset },
                    { .method = SystemInterfaceMethod::DelayUs, .delayUs = HX711Driver::TimingDelayUs }
            };

    vector<SystemInterfaceCall> allBitsSequence;
    for (int i = 0; i < HX711Driver::AdcBits; ++i)
        AppendVector(allBitsSequence, singleBitSequence);

    vector<SystemInterfaceCall> entireSequence;

    // Check data ready
    entireSequence.push_back({ .method = SystemInterfaceMethod::GetPinState });

    // Sequence to read all ADC bits
    AppendVector(entireSequence, allBitsSequence);

    // One clock pulse to set gain for next conversion
    entireSequence.push_back({ .method = SystemInterfaceMethod::SetPinState, .gpioState = GpioPinState::Set });
    entireSequence.push_back({ .method = SystemInterfaceMethod::DelayUs, .delayUs = HX711Driver::TimingDelayUs });
    entireSequence.push_back({ .method = SystemInterfaceMethod::SetPinState, .gpioState = GpioPinState::Reset });

    // When
    int32_t adcValue = 0;
    ASSERT_TRUE(mHx711.ReadAdcValue(adcValue));

    // Then
    ASSERT_EQ(mSystem.Calls.size(), entireSequence.size());
    for (int i = 0; i < entireSequence.size(); ++i)
        ASSERT_EQ(mSystem.Calls[i], entireSequence[i]);
}