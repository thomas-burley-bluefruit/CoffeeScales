#include "DisplayItemSpy.h"
#include "DisplayManager.h"
#include "DisplaySpy.h"
#include "gtest/gtest.h"

#include <vector>

using namespace ::coffeescales::display;

class DisplayManagerTestObject : public DisplayManager
{
  public:
    DisplayManagerTestObject(DisplayInterface& display) :
        DisplayManager(display)
    {
    }

    static constexpr size_t MaxDisplayItems = DisplayManager::MaxDisplayItems;
    uint32_t& DisplayItemCount = mDisplayItemCount;
    std::array<DisplayItemInterface*, MaxDisplayItems>& DisplayItems = mDisplayItems;
};

class DisplayManagerTests : public testing::Test
{
  public:
    DisplayManagerTests() :
        mDisplayManager(mDisplay)
    {
    }

    DisplaySpy mDisplay;
    DisplayManagerTestObject mDisplayManager;
};

TEST_F(DisplayManagerTests, Can_register_display_item)
{
    DisplayItemSpy displayItem;
    ASSERT_TRUE(mDisplayManager.RegisterDisplayItem(&displayItem));
    ASSERT_EQ(mDisplayManager.DisplayItemCount, 1);
    ASSERT_EQ(mDisplayManager.DisplayItems[0], &displayItem);
}

TEST_F(DisplayManagerTests, Can_only_register_up_to_max_display_items)
{
    // Given, when
    DisplayItemSpy displayItem;
    for (size_t i = 0; i < DisplayManagerTestObject::MaxDisplayItems; ++i)
        ASSERT_TRUE(mDisplayManager.RegisterDisplayItem(&displayItem));

    // Then
    ASSERT_EQ(mDisplayManager.MaxDisplayItems, mDisplayManager.DisplayItemCount);
    ASSERT_FALSE(mDisplayManager.RegisterDisplayItem(&displayItem));
}

TEST_F(DisplayManagerTests, Init_dies_when_no_display_items_registered)
{
    EXPECT_DEATH(mDisplayManager.Init(), "");
}

TEST_F(DisplayManagerTests, Init_calls_init_on_single_registered_display_item)
{
    // Given
    DisplayItemSpy displayItem;
    mDisplayManager.RegisterDisplayItem(&displayItem);

    // When
    mDisplayManager.Init();

    // Then
    ASSERT_TRUE(displayItem.InitCalled);
}

TEST_F(DisplayManagerTests, Init_calls_init_on_multiple_registered_display_items)
{
    // Given
    std::vector<DisplayItemSpy> displayItems(mDisplayManager.MaxDisplayItems, DisplayItemSpy());
    for (auto& item : displayItems)
    {
        mDisplayManager.RegisterDisplayItem(&item);
    }

    // When
    mDisplayManager.Init();

    // Then
    for (auto& item : displayItems)
    {
        ASSERT_TRUE(item.InitCalled);
    }
}

TEST_F(DisplayManagerTests, Task_calls_update_on_single_registered_display_item)
{
    // Given
    DisplayItemSpy displayItem;
    mDisplayManager.RegisterDisplayItem(&displayItem);

    // When
    mDisplayManager.Task();

    // Then
    ASSERT_TRUE(displayItem.UpdateCalled);
}

TEST_F(DisplayManagerTests, Task_calls_update_on_multiple_registered_display_items)
{
    // Given
    std::vector<DisplayItemSpy> displayItems(mDisplayManager.MaxDisplayItems, DisplayItemSpy());
    for (auto& item : displayItems)
    {
        mDisplayManager.RegisterDisplayItem(&item);
    }

    // When
    mDisplayManager.Task();

    // Then
    for (auto& item : displayItems)
    {
        ASSERT_TRUE(item.UpdateCalled);
    }
}

TEST_F(DisplayManagerTests, Task_redraws_screen_if_single_registered_display_item_required_redraw)
{
    // Given
    DisplayItemSpy displayItem;
    displayItem.RedrawRequired = true;
    mDisplayManager.RegisterDisplayItem(&displayItem);

    // When
    mDisplayManager.Task();

    // Then
    ASSERT_TRUE(mDisplay.RedrawCalled);
}

TEST_F(DisplayManagerTests, Task_redraws_screen_if_any_display_item_requires_redraw)
{
    // Given
    std::vector<DisplayItemSpy> displayItems(mDisplayManager.MaxDisplayItems, DisplayItemSpy());
    for (auto& item : displayItems)
    {
        mDisplayManager.RegisterDisplayItem(&item);
    }

    int randomIndex = rand() % (mDisplayManager.MaxDisplayItems - 1);
    displayItems[randomIndex].RedrawRequired = true;

    // When
    mDisplayManager.Task();

    // Then
    ASSERT_TRUE(mDisplay.RedrawCalled);
}