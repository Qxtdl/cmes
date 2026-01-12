#include "../../../taulib/heap.h"
#include "../../../taulib/stdio.h"
#include "../../../taulib/string.h"

void c_malloc(int argc, char *argv[]) {
    malloc(hex_to_u16(argv[0]) - 1);
}