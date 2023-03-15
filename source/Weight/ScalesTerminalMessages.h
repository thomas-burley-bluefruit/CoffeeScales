#pragma once

namespace coffeescales::weight
{

struct ScalesTerminalMessages
{
    static constexpr char const *CalibratePlaceWeight = "Place a 100g weight on the scales.\nIssue \"scales calibrate set\" when ready.\n";
    static constexpr char const *AdcPrintFormat = "Last ADC reading: %i\n";
    static constexpr char const *WeightPrintFormat = "Last weight conversion: %img\n";
};

}
