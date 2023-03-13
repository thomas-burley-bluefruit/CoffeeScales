#include "Application.h"

static coffeescales::Application mApplication;

int main()
{
    mApplication.Init();
    mApplication.Loop();
}
