#include "gtest/gtest.h"
#include "Utilities.h"
#include <bitset>

using namespace ::coffeescales::drivers;
using std::bitset;

TEST(UtilitiesTests, Twos_complement_to_int_positive_value)
{
    int32_t value = 0x1E240;
    bitset<24> data(value);
    ASSERT_EQ(value, Utilities::TwosComplementToInt(data));
}

TEST(UtilitiesTests, Twos_complement_to_int_max_positive_value)
{
    int32_t value = 0x7FFFFF;
    bitset<24> data(value);
    ASSERT_EQ(value, Utilities::TwosComplementToInt(data));
}

TEST(UtilitiesTests, Twos_complement_to_int_negative_value)
{
    uint32_t value = 0x1E240;
    bitset<24> data(value);
    data.flip();
    data = bitset<24>(data.to_ulong() + 1);

    ASSERT_EQ(-static_cast<int32_t>(value), Utilities::TwosComplementToInt(data));
}

TEST(UtilitiesTests, Twos_complement_to_int_max_negative_value)
{
    uint32_t value = 0x800000;
    bitset<24> data(value);
    data.flip();
    data = bitset<24>(data.to_ulong() + 1);

    ASSERT_EQ(-static_cast<int32_t>(value), Utilities::TwosComplementToInt(data));
}

TEST(UtilitiesTests, Twos_complement_to_int_zero_value)
{
    bitset<24> data;
    ASSERT_EQ(0, Utilities::TwosComplementToInt(data));
}

TEST(UtilitiesTests, Int_to_twos_complement_positive_value)
{
    const int value = 65432;
    const size_t bits = 24;
    bitset<bits> expected(value);
    auto actual = Utilities::IntToTwosComplement<bits>(value);
    ASSERT_EQ(expected, actual);
}

TEST(UtilitiesTests, Int_to_twos_complement_max_positive_value)
{
    const int value = 0x7FFFFF;
    const size_t bits = 24;
    bitset<bits> expected(value);
    auto actual = Utilities::IntToTwosComplement<bits>(value);
    ASSERT_EQ(expected, actual);
}

TEST(UtilitiesTests, Int_to_twos_complement_negative_value)
{
    const int value = -123123;
    const size_t bits = 24;
    bitset<bits> expected(abs(value));
    expected.flip();
    expected = bitset<bits>(expected.to_ulong() + 1);

    auto actual = Utilities::IntToTwosComplement<bits>(value);

    ASSERT_EQ(expected, actual);
    ASSERT_EQ(value, Utilities::TwosComplementToInt(actual));
}