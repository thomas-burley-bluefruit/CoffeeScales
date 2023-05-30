#include "board_SSD1322.h"
#include "DisplayGpio.h"

static constexpr bool DataState = true;
static constexpr bool CommandState = false;

extern "C"
{

    void init_board(GDisplay* g) {}

    void setpin_reset(GDisplay* g, gBool state)
    {
        DisplayGpio_SetResetPin(!state);
    }

    void acquire_bus(GDisplay* g)
    {
        (void)g;
    }

    void release_bus(GDisplay* g)
    {
        (void)g;
    }

    void write_cmd(GDisplay* g, gU8 cmd)
    {
        DisplayGpio_SetDcPin(CommandState);
        DisplayGpio_Transmit(&cmd, 1);
    }

    void write_data(GDisplay* g, gU8 data)
    {
        DisplayGpio_SetDcPin(DataState);
        DisplayGpio_Transmit(&data, 1);
    }

    void post_init_board(GDisplay* g) {}
}
