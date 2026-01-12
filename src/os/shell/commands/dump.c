#include "../../filesystem/fs.h"
#include "../../../taulib/stdio.h"

void dump(int argc, char *argv[]) {
    u16 addr = hex_to_u16(argv[0]);
    u16 amount = hex_to_u16(argv[1]);
    for (int i = 0; i < amount; i++)
        putc(*(char *)(addr + i));
}