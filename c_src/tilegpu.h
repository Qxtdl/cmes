/*
    Header-only libary for tile drawing functions.
    For brutus's tile-based GPU.
    Meant to run on Taurus RV32I System.
*/

#ifndef TILEGPU_H
#define TILEGPU_H

#include "globals.h"

#define TILEGPU_START_CLEAR ((volatile u8 *)0xFFFF)  // 2 bits, to start drawing/clear the screen
#define TILEGPU_TILEGPU_X   ((volatile u8 *)0xFFFE)  // x cord
#define TILEGPU_TILEGPU_Y   ((volatile u8 *)0xFFFD)  // y cord
#define TILEGPU_TILEADDR    ((volatile u16 *)0xFFFB) // tile id low byte
#define TILEGPU_FX_OPCODE   ((volatile u8 *)0xFFFA)  // effects opcode
#define TILEGPU_FX_IMM      ((volatile u16 *)0xFFF8) // effects color value

// Draw a tile at the specified (x, y) coordinates with the given tile ID.
// Coordinates are in pixel units.
void tilegpu_draw(u8 x, u8 y, u16 tile_id)
{
    *TILEGPU_TILEGPU_X = x;
    *TILEGPU_TILEGPU_Y = y;
    *TILEGPU_TILEADDR = tile_id;
    *TILEGPU_START_CLEAR = 2;
}

// Draw a tile at the specified (x, y) coordinates with the given tile ID.
// Coordinates are in pixel units.
// Apply special effects based on fx_op and fx_imm parameters.

// fx opcodes
#define NO_FX   0
#define AND_COLOR 1
#define NAND_COLOR 2
#define XOR_COLOR 3
#define OR_COLOR 4
#define NOR_COLOR 5

void tilegpu_fxdraw(u8 x, u8 y, u16 tile_id, u8 fx_op, u16 fx_imm)
{
    *TILEGPU_FX_OPCODE = fx_op;
    *TILEGPU_FX_IMM = fx_imm;
    tilegpu_draw(x,y,tile_id);
}

// Clear the entire screen.
void tilegpu_clearscreen(void)
{
    *TILEGPU_START_CLEAR = 0b01;
}

// Print a null-terminated string at the specified (x, y) coordinates.
// (this is too dang slow)
void tilegpu_puts(u8 x, u8 y, const char *str)
{   
    u8 pos_x=x, pos_y=y;
    for (u16 i = 0; str[i]!='\0'; i++) 
    {
        tilegpu_draw(pos_x++, pos_y, (u16)str[i]);
        if ((s8)pos_x>=48) {pos_x=0;pos_y++;}
    }
}

#endif // TILEGPU_H