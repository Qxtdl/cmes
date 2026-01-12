#include "../../../taulib/stdio.h"
#include "../../../taulib/string.h"

void wtxt(int argc, char *argv[]) {
    char *input = gets();

    u32 addr_val = hex_to_u16(argv[0]);
    char *addr = (char *)addr_val;

    u32 len = strlen(input);

    for (u32 i = 0; i < len; i++) {
        addr[i] = input[i];
    }

    addr[len] = '\0';
}
