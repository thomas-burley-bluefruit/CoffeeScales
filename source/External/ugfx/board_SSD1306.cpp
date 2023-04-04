#include <cstring>
#include "board_SSD1306.h"
#include "DisplayGpio.h"

static constexpr bool DataState = true;
static constexpr bool CommandState = false;

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
    DisplayGpio_SetDcPin(CommandState);
    DisplayGpio_SetChipSelect(false);
    DisplayGpio_Transmit(&cmd, 1);
    DisplayGpio_SetChipSelect(true);
}

void write_data(GDisplay *g, gU8 *data, gU16 length)
{
    DisplayGpio_SetDcPin(DataState);
    DisplayGpio_SetChipSelect(false);
    DisplayGpio_Transmit(data, length);
    DisplayGpio_SetChipSelect(true);
}

void post_init_board(GDisplay *g)
{
}

}
