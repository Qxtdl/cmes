#include <stdint.h>

#include "../../filesystem/fs.h"
#include "../../../taulib/stdio.h"
#include "../../../taulib/legacy_hex.h"

void dump(int argc, char *argv[]) {
    uintptr_t addr = hex_str_to_u32(argv[0]);
    u16 amount = hex_str_to_u32(argv[1]);
    if (*argv[2] == 'a')
        for (int i = 0; i < amount; i++)
            putc(*(char *)(addr + i));
    else if (*argv[2] == 'h')
        for (int i = 0; i < amount; i++) {
            puts(u8_to_dec(*(char *)(addr + i)));
            putc(' ');
        }
}