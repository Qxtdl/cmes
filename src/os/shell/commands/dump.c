#include <stdint.h>

#include "../../filesystem/fs.h"
#include "../../../taulib/stdio.h"

void dump(int argc, char *argv[]) {
    uintptr_t addr = hex_str_to_u32(argv[0]);
    u16 amount = hex_str_to_u32(argv[1]);
    for (int i = 0; i < amount; i++)
        putc(*(char *)(addr + i));
}