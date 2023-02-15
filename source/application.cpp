#include "application.h"

#include "stm32l4xx_ll_gpio.h"
#include "main.h"

extern "C" {

void setup() {
    // For future episodes ;)
}

void loop() {
    LL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

    HAL_Delay(200U);
}

}