#include "Application.h"

static Application mApplication;

int main()
{
    mApplication.Init();
    mApplication.Loop();
}
