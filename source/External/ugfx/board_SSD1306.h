/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#include "gfx.h"

//#define SSD1306_PAGE_PREFIX		0x40

#ifdef __cplusplus
extern "C" {
#endif

void init_board(GDisplay *g);
void setpin_reset(GDisplay *g, gBool state);
void acquire_bus(GDisplay *g);
void release_bus(GDisplay *g);
void write_cmd(GDisplay *g, gU8 cmd);
void write_data(GDisplay *g, gU8 *data, gU16 length);
void post_init_board(GDisplay *g);

#ifdef __cplusplus
}
#endif


#endif /* _GDISP_LLD_BOARD_H */
