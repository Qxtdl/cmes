#include "../../../taulib/heap.h"
#include "../../../taulib/stdio.h"
#include "../../../taulib/string.h"

void c_malloc(int argc, char *argv[]) {
    malloc(hex_str_to_u32(argv[0]) - 1);
}