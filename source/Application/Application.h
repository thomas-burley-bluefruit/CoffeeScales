#pragma once

namespace coffeescales
{

class Application
{
public:
    static void Init();
    [[noreturn]] static void Loop();
};

}