#pragma once

namespace coffeescales::weight
{

struct ScalesTerminalMessages
{
    static constexpr char const *CalibratePlaceWeight = "Place a 200g weight on the scales.\nIssue \"scales calibrate set\" when ready.\n";
    static constexpr char const *CalibrateComplete = "Calibration successful.\n";
    static constexpr char const *AdcPrintFormat = "Last ADC reading: %li\n";
    static constexpr char const *WeightPrintFormat = "Last weight conversion: %limg\n";
};

}
