#include <stdint.h>

#include "../../../taulib/heap.h"
#include "../../../taulib/stdio.h"
#include "../../../taulib/string.h"

void hex(int argc, char *argv[]) {
    while (1) {
        char *input = gets();
        if (!strcmp(input, "exit")) return;
        uintptr_t address = hex_str_to_u32(input);
        putc('\n');
        *(u8 *)address = hex_str_to_u32(gets());
    }
}