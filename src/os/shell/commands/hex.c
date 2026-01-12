#include "../../../taulib/heap.h"
#include "../../../taulib/stdio.h"
#include "../../../taulib/string.h"

void hex(int argc, char *argv[]) {
    while (1) {
        char *address_str = input("A: ");
        if (!strcmp(address_str, "exit")) return;
        u16 address = hex_to_u16(address_str);
        char *value_str = input("V: ");
        u8 value = hex_to_u8(value_str);
        *(char *)address = value;
    }
}