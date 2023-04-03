#pragma once

#include <cstdint>

extern "C"
{

void Spi3_MspInit(void);
void DisplayGpio_Init();
bool DisplayGpio_Transmit(const uint8_t *data, uint16_t size);
void DisplayGpio_SetChipSelect(bool state);
void DisplayGpio_SetResetPin(bool state);

}
