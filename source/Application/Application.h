#pragma once

extern "C" void TestFunc();

namespace coffeescales
{

class Application
{
public:
    static void Init();
    [[noreturn]] static void Loop();
};

}