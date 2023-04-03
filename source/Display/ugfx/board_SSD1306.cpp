#include <cstring>
#include "board_SSD1306.h"
#include "DisplayGpio.h"

extern "C"
{

void init_board(GDisplay *g)
{
}

void setpin_reset(GDisplay *g, gBool state)
{
    DisplayGpio_SetResetPin(!state);
}

void acquire_bus(GDisplay *g)
{
    (void) g;
}

void release_bus(GDisplay *g)
{
    (void) g;
}

void write_cmd(GDisplay *g, gU8 cmd)
{
    gU8 data[2]{0};
    data[0] = cmd;
    DisplayGpio_SetChipSelect(false);
    DisplayGpio_Transmit(data, 1);
    DisplayGpio_SetChipSelect(true);
}

void write_data(GDisplay *g, gU8 *data, gU16 length)
{

    gU8 txData[2];
    txData[1] = 1;
    DisplayGpio_SetChipSelect(false);
    for (size_t i = 0; i < length; i++)
    {
        txData[0] = data[i];
        DisplayGpio_Transmit(txData, 1);
    }
    DisplayGpio_SetChipSelect(true);
}

void post_init_board(GDisplay *g)
{
//    DisplayGpio_SetResetPin(true);
}

}
