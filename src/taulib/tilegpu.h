/*
    Header-only libary for the tile-based GPU by Brutus.
    - Meant to run on Taurus RV32I System.
*/


#ifndef TILEGPU_H
#define TILEGPU_H

#include "globals.h"
#include "memorymap.h" // Not really needed, just in case

#define TILEGPU_X           ((volatile u8  *)0xFFFF)
#define TILEGPU_Y           ((volatile u8  *)0xFFFE)
#define TILEGPU_ADDR        ((volatile u16 *)0xFFFC)
#define TILEGPU_FX_OPCODE   ((volatile u8  *)0xFFFB)
#define TILEGPU_FX_IMM      ((volatile u16 *)0xFFFA)
#define TILEGPU_DRAW        1
#define TILEGPU_CLEAR       2
#define TILEGPU_CONTROLS    ((volatile u8  *)0xFFF9)

// Draw a tile at the specified (x, y) coordinates with the given tile ID.
// Coordinates are in pixel units.
static void tilegpu_draw(u8 x, u8 y, u16 tile_id)
{
    *TILEGPU_X = x;
    *TILEGPU_Y = y;
    *TILEGPU_ADDR = tile_id;
    *TILEGPU_CONTROLS = TILEGPU_DRAW;
}

// Draw a tile at the specified (x, y) coordinates with the given tile ID.
// Coordinates are in pixel units.
// Apply special effects based on fx_op and fx_imm parameters.

// fx opcodes
#define NO_FX       0
#define AND_COLOR   1
#define NAND_COLOR  2
#define XOR_COLOR   3
#define OR_COLOR    4
#define NOR_COLOR   5

static void tilegpu_fxdraw(u8 x, u8 y, u16 tile_id, u8 fx_op, u16 fx_imm)
{
    *TILEGPU_FX_OPCODE = fx_op;
    *TILEGPU_FX_IMM = fx_imm;
    tilegpu_draw(x, y, tile_id);
}

// Clear the entire screen.
static void tilegpu_clearscreen(void)
{
    *TILEGPU_CONTROLS = TILEGPU_CLEAR;
}

// Print a null-terminated string at the specified (x, y) coordinates.
static void tilegpu_puts(u8 x, u8 y, const char *str)
{   
    u8 x2 = x, y2 = y;
    for (u16 i = 0; str[i] != '\0'; i++) 
    {
        if (str[i] == '\n') y2+=2;
        tilegpu_draw(x2++, y2, str[i]);
        if (x2 >= 48 || str[i] == '\n') 
        {
            x2 = 0;
            y2+=2;
        }
    }
}

static void tilegpu_print(const char *str) {
    static u8 y = 0;
    tilegpu_puts(0, y+=2, str);
    if (y == 64) {
        y = 0;
        *TILEGPU_CONTROLS = TILEGPU_CLEAR;
    }
}

#endif // TILEGPU_H