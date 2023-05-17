#include "gtest/gtest.h"

#include "BrewTimer.h"
#include "SystemMock.h"

using namespace ::coffeescales;
using namespace ::coffeescales::time;

class BrewTimerTests : public testing::Test
{
public:
    BrewTimerTests() : mBrewTimer(mSystem)
    {}

  halwrapper::SystemMock mSystem;
  BrewTimer mBrewTimer;
};

TEST_F(BrewTimerTests, Can_register_callback)
{
    ASSERT_TRUE(mBrewTimer.RegisterCallback(&mCallback));
    ASSERT_EQ(mBrewTimer.CallbackCount, 1);
    ASSERT_EQ(mBrewTimer.Callbacks[0], &mCallback);
}